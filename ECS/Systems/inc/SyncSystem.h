#ifndef ECS_SYNCSYSTEM_H
#define ECS_SYNCSYSTEM_H

#include "BaseSystem.h"
#include "events.h"
#include "event.h"
#include <iostream>
#include "Packets.h"

using std::cout;
using std::endl;

#ifndef INFO
#define INFO __FILE__ << ":" << __LINE__
#endif


const int SyncSystemID = 1219;

class SyncSystem : public BaseSystem {

public:


    static constexpr sf::Int8 SYNC_POS_ID = 1;
    static constexpr sf::Int8 SYNC_VEL_ID = 2;
    static constexpr sf::Int8 SYNC_HP_ID =  3;

    static constexpr sf::Int8 END_ENTITY_DESCRIPTION = -128;


    virtual int getSystemID() override
    {
        return SyncSystemID;
    }

    virtual void update(EntityManager* manager) override
    {
//        std::cout << ">>>>>>>>>>>>>> sync system work" << std::endl;


        std::vector<Entity *> test_entities;
        manager->selectEntites<PlayerComponent>(test_entities);
        cout << "[syncsys] " << INFO << " TEST SYNC test_entities.size=" << test_entities.size() << endl;
        for (auto& e : test_entities)
        {
            cout << "   e.id=" << e->id
                 << " has_sync=" << e->HasComponent<SinkableComponent>()
                 << " is_remote=" << e->getComponent<PlayerComponent>().is_remote
                 << " addr e=" << e
                 << std::endl;
        }

        if (Game::instance->network->isClient())
        {
            sf::Packet pack;
            std::vector<Entity *> players_to_sync;
            manager->selectEntites<SinkableComponent, PlayerComponent>(players_to_sync);
            cout << "[syncsys] " << INFO << " update client players_to_sync.size=" << players_to_sync.size() << endl;

            pack << Packets::SyncPlayerFromClient;

            for (auto &e : players_to_sync)
            {
                if ( ! e->getComponent<PlayerComponent>().is_remote)
                    writeEntity(pack, e);
            }

            SyncSystemSyncEvent event;
            event.pack = &pack;
            Events::fire(Events::EventType::SyncSystemClientToHostSendSync, &event);
        }
        else if (Game::instance->network->isHost())
        {

            sf::Packet pack;
            std::vector<Entity *> need_sync;
            manager->selectEntites<SinkableComponent>(need_sync);
            cout << "[syncsys] " << INFO << " update host need_sync.size=" << need_sync.size() << endl;

            pack << Packets::SyncAllEntitiesFromHost;

            for (auto &e : need_sync)
            {
                writeEntity(pack, e);
            }

            SyncSystemSyncEvent event;
            event.pack = &pack;
            Events::fire(Events::EventType::SyncSystemHostToClientSendSync, &event);
        }

    }

    virtual bool added() override
    {

        Events::on(Events::EventType::NetworkSyncAllFromHostRecieved, [this](OurEvent *event)
        {
            cout << "[syncsys] " << INFO << " NetworkSyncAllFromHostRecieved event process" << endl;
            auto *e = dynamic_cast<NetworkSyncFromHostEvent*>(event);
            updateEntitiesFromPacket(*e->pack);
//            e->pack;
        });

        Events::on(Events::EventType::NetworkSyncPlayerFromClientEvent, [this](OurEvent *event)
        {
            cout << "[syncsys] " << INFO << " NetworkSyncPlayerFromClientEvent event process" << endl;
            auto *e = dynamic_cast<NetworkSyncPlayerFromClientEvent*>(event);
            updateEntitiesFromPacket(*e->pack);
//            e->pack;
        });

        std::cout << "[syncsys] " << INFO << " sync system events subscribed" << std::endl;


        return true;
    }

    virtual ~SyncSystem() override
    {

    }


    void updateEntitiesFromPacket(sf::Packet& pack)
    {
        std::vector<Entity *> need_sync;
        Game::instance->entityManager->selectEntites<SinkableComponent>(need_sync);

        while (true)
        {
            sf::Int32 id;
            if (!(pack >> id))
                break;

            Entity *ent = getByIdOrNull(need_sync, id);

            if (ent == nullptr)
            {
                skipBytesUntilEntityEnd(pack);
                continue;
            }

//            cout << "[syncsys] get id=" << tmp_id << " ent=" << ent << endl;

            // TODO: не синкать локального игрока

            readEntity(pack, ent);
        }

    }

    Entity* getByIdOrNull(std::vector<Entity *> &entities, int id)
    {
        for (auto &e : entities)
        {
            if (e->id == id)
                return e;
        }
        return nullptr;
    }

    inline void writeEntity(sf::Packet& pack, Entity *e)
    {
        pack << sf::Int32(e->id);

        if (e->HasComponent<PositionComponent>())
        {
            auto& pos = e->getComponent<PositionComponent>();
            pack << SYNC_POS_ID;
            pack << pos.position.x;
            pack << pos.position.y;
        }

        if (e->HasComponent<VelocityComponent>())
        {
            auto& vel = e->getComponent<VelocityComponent>();
            pack << SYNC_VEL_ID;
            pack << vel.velocity.x;
            pack << vel.velocity.y;
        }

        if (e->HasComponent<HealthComponent>())
        {
            auto& hp = e->getComponent<HealthComponent>();
            pack << SYNC_HP_ID;
            pack << sf::Int32(hp.health);
        }

        // frames component
        // direction component

        pack << END_ENTITY_DESCRIPTION;
    }


    inline void readEntity(sf::Packet& pack, Entity *e)
    {
        sf::Int8 comp_id;
        while ((pack >> comp_id) && comp_id != END_ENTITY_DESCRIPTION)
        {
            // TODO добавлять отсутствующий компонент?
            switch (comp_id) {
                case SYNC_POS_ID:
                    if (e->HasComponent<PositionComponent>())
                    {
                        auto& pos = e->getComponent<PositionComponent>();
                        pack >> pos.position.x >> pos.position.y;
                    }
                    break;
                case SYNC_VEL_ID:
                    if (e->HasComponent<VelocityComponent>())
                    {
                        auto& vel = e->getComponent<VelocityComponent>();
                        pack >> vel.velocity.x >> vel.velocity.y;
                    }
                    break;
                case SYNC_HP_ID:
                    if (e->HasComponent<HealthComponent>())
                    {
                        auto& hp = e->getComponent<HealthComponent>();
                        sf::Int32 tmp_health;
                        pack >> tmp_health;
                        hp.health = tmp_health;
                    }
                    break;
                default:
                    break;
            }
        }


    }

    void skipBytesUntilEntityEnd(sf::Packet &pack)
    {
        sf::Int8 comp_id;
        sf::Int32 tmp_int32;
        float tmp_float;

        // просто идем до конца описания сущности и ситаем байты
        while ((pack >> comp_id) && comp_id != END_ENTITY_DESCRIPTION)
        {
            switch (comp_id) {
                case SYNC_POS_ID:
                    pack >> tmp_float >> tmp_float;
                    break;
                case SYNC_VEL_ID:
                    pack >> tmp_float >> tmp_float;
                    break;
                case SYNC_HP_ID:
                    pack >> tmp_int32;
                    break;
                default:
                    break;
            }
        }

    }


//    void updateCertian

};


#endif //ECS_SYNCSYSTEM_H
