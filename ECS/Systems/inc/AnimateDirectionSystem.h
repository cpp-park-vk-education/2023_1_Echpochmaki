#ifndef GAME_ANIMATEDIRECTIONSYSTEM_H
#define GAME_ANIMATEDIRECTIONSYSTEM_H

#endif //GAME_ANIMATEDIRECTIONSYSTEM_H

#include "../../inc/EntityManager.h"
#include "BaseSystem.h"
#include "MoveDirectionComponent.h"
#include "VelocityComponent.h"
#include "SpriteComponent.h"


using TypeID = size_t;

constexpr TypeID ID = 14345;

class AnimateDirectionSystem : public BaseSystem {

    int getSystemID() override
    {
        return ID;
    }

    void update(EntityManager* manager) override {
        std::vector<Entity*> entities;
        manager->selectEntites<MoveDirectionComponent>(entities);

        for (auto entity: entities) {
            //if (entity->HasComponent<VelocityComponent>() && entity->HasComponent<SpriteComponent>())
            //{
                //auto velocity = entity->getComponent<VelocityComponent>();
                auto dir_component = entity->getComponent<MoveDirectionComponent>();

                if (dir_component.has_dir_changed)
                {
                    auto rect = entity->getComponent<SpriteComponent>().sprite.getTextureRect();
                    rect.left += rect.width;
                    rect.width = -rect.width;

                    entity->getComponent<SpriteComponent>().sprite.setTextureRect(rect);
                }
//                else if (velocity.velocity.x < 0)
//                {
//                    auto rect = entity->getComponent<SpriteComponent>().sprite.getTextureRect();
//                    rect.left -= rect.width;
//                    rect.width = -rect.width;
//
//                    entity->getComponent<SpriteComponent>().sprite.setTextureRect(rect);
//                }

            //}
        }
    }

    virtual bool added() override {
        return true;
    }
};
