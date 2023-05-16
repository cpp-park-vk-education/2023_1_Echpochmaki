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
    virtual int getSystemID() override
    {
        return SyncSystemID;
    }

    virtual void update(EntityManager* manager) override
    {
//        std::cout << ">>>>>>>>>>>>>> sync system work" << std::endl;

        if (Game::instance->network->isClient())
        {

            sf::Packet pack;
            std::vector<Entity *> players;
            manager->selectEntites<PlayerComponent>(players);

            pack << Packets::SyncPlayerFromClient;

            for (auto &e : players)
            {
                if (e->HasComponent<PositionComponent>())
                {
                    auto& pos = e->getComponent<PositionComponent>();
                    pack << sf::Int32(e->id);
                    pack << pos.position.x;
                    pack << pos.position.y;
                }
            }

            SyncSystemSyncEvent event;
            event.pack = &pack;
            Events::fire(Events::EventType::SyncSystemClientToHostSendSync, &event);
        }
        else if (Game::instance->network->isHost())
        {

            sf::Packet pack;
            std::vector<Entity *> with_position;
            manager->selectEntites<PositionComponent>(with_position);

            pack << Packets::SyncAllEntitiesFromHost;

            for (auto &e : with_position)
            {
                auto& pos = e->getComponent<PositionComponent>();
                pack << sf::Int32(e->id);
                pack << pos.position.x;
                pack << pos.position.y;
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
        auto& entities = Game::instance->entityManager->entities;

        sf::Int32 tmp_id;
        float tmp_coord;
        while (pack >> tmp_id)
        {
            Entity *ent = getByIdOrNull(entities, tmp_id);
//            cout << "[syncsys] get id=" << tmp_id << " ent=" << ent << endl;
            if (ent && ent->HasComponent<PositionComponent>())
            {
                auto& pos = ent->getComponent<PositionComponent>();
                pack >> pos.position.x >> pos.position.y;
//                cout << "      has pos pos component; received x=" << pos.position.x << " y=" << pos.position.y << endl;
            }
            else
            {
//                cout << "      skipped pos values " << endl;
                pack >> tmp_coord >> tmp_coord;
            }
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

//    void updateCertian

};


#endif //ECS_SYNCSYSTEM_H
