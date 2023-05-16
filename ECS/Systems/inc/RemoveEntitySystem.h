#ifndef GAME_REMOVEENTITYSYSTEM_H
#define GAME_REMOVEENTITYSYSTEM_H

#include "BaseSystem.h"
#include "../../inc/EntityManager.h"
#include "HealthComponent.h"
#include "PlayerComponent.h"
#include "PositionComponent.h"

const int RemoveSystemId = 32342521;

class RemoveSystem : public BaseSystem {
public:
    RemoveSystem() : ID(RemoveSystemId) {}

    virtual void update(EntityManager *manager)
    {
        std::cout << "Die die die my darling" << std::endl;
        std::vector<Entity*> entities;
        manager->selectEntites<HealthComponent>(entities);

        for (auto entity: entities)
        {
            auto& healthComponent = entity->getComponent<HealthComponent>();

            if (healthComponent.health <= 0)
            {
	            entity->getComponent<FramesComponent>().dying = true;
				if (entity->getComponent<FramesComponent>().died)
                {
                    if (entity->HasComponent<PlayerComponent>())
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
                        manager->deleteEntity(entity);
                    }
                }

            }

        }

    }

    virtual int getSystemID() override {
        return ID;
    }


    virtual bool added() {
        ID = RemoveSystemId; //TODO::find out what to return
        return true;
    }

    ~RemoveSystem() override = default;

private:
    int ID;
};

#endif //GAME_REMOVEENTITYSYSTEM_H
