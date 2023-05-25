#ifndef GAME_REMOVEENTITYSYSTEM_H
#define GAME_REMOVEENTITYSYSTEM_H

#include "BaseSystem.h"
#include "../../inc/EntityManager.h"
#include "HealthComponent.h"
#include "PlayerComponent.h"
#include "PositionComponent.h"
#include "events.h"
#include <iostream>
#include "Game.h"
#include "Packets.h"

using std::cout;
using std::endl;

#ifndef INFO
#define INFO __FILE__ << ":" << __LINE__
#endif


const int RemoveSystemId = 32342521;

class RemoveSystem : public BaseSystem {
public:
    RemoveSystem() : ID(RemoveSystemId) {

    }

    virtual void update(EntityManager *manager)
    {
//        std::cout << "Die die die my darling" << std::endl;
        std::vector<Entity*> entities;
        manager->selectEntites<HealthComponent>(entities);

        sf::Packet pack;
        pack << Packets::DeleteEntitiesByIds;
        int amount_deleted = 0;

        for (auto entity: entities)
        {
            auto& healthComponent = entity->getComponent<HealthComponent>();

            if (healthComponent.health <= 0)
            {
	            entity->getComponent<FramesComponent>().dying = true;
				if (entity->getComponent<FramesComponent>().died)
                {
                    if (entity->HasComponent<PlayerComponent>() && ! entity->getComponent<PlayerComponent>().is_remote) // подумать
                    {
                        sf::Font default_font;
                        default_font.loadFromFile("../Graphics/fonts/main_font.ttf");
                        sf::Text info;
                        std::string msg = "You died";
                        info.setString(msg);
                        info.setFont(default_font);
                        info.setCharacterSize(30);

                        Vector2f position = entity->getComponent<PositionComponent>().position;
                        //auto& view = window->getView();
                        info.setPosition(position.x, position.y);

                        entity->getComponent<PositionComponent>().position = {100, 100};
                        entity->getComponent<HealthComponent>().health = 100;
                        entity->getComponent<PlayerComponent>().deaths += 1;
                    }
                    else {
                        ++amount_deleted;
                        pack << sf::Int32(entity->id);
//                        cout << "   packed id=" << sf::Int32(entity->id) << endl;
                        manager->deleteEntity(entity);
                    }
                }




            }

        }

        cout << "[removesys] " << INFO << " update amount_deleted=" << amount_deleted << endl;
        if (amount_deleted > 0)
        {
            NetworkDeleteEntitiesByIdsSendEvent event;
            event.pack = &pack;
            Events::fire(Events::EventType::NetworkDeleteEntitiesByIdsSend, &event);
        }

    }

    virtual int getSystemID() override {
        return ID;
    }


    virtual bool added() {

        Events::on(Events::EventType::NetworkDeleteEntitiesByIds, [this](OurEvent *event){
            auto *e = dynamic_cast<NetworkDeleteEntitiesByIdsReceivedEvent*>(event);
            sf::Packet& pack = *e->pack;
            cout << "[removesys] " << INFO << " NetworkDeleteEntityByIds event process packet.size=" << pack.getDataSize() << endl;

            sf::Int32 id;
            while (pack >> id)
            {
                bool deleted = Game::instance->entityManager->deleteEntityById(id);
                cout << "   entity id=" << id << " was deleted=" << deleted << endl;
            }

        });

        ID = RemoveSystemId; //TODO::find out what to return
        return true;
    }

    ~RemoveSystem() override = default;

private:
    int ID;
};

#endif //GAME_REMOVEENTITYSYSTEM_H
