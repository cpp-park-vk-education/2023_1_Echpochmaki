#ifndef ECS_MOVESYSTEM_H
#define ECS_MOVESYSTEM_H

#include <cmath>

#include "BaseSystem.h"
#include "../../inc/EntityManager.h"
#include "../../inc/ECS.h"
#include "PositionComponent.h"
#include "VelocityComponent.h"
#include "CollisionComponent.h"
#include "EnemyComponent.h"
#include "MoveDirectionComponent.h"
#include "AnimationMovingComponent.h"
#include "FramesComponent.h"





const int MoveSystemID = 2;

class MoveSystem : public BaseSystem {
public:
    virtual int getSystemID() override {
        return MoveSystemID;
    }

    virtual void update(EntityManager *manager) override {
        std::vector<Entity *> entities;
        manager->selectEntites<PositionComponent>(entities);

        // кажется теперь не нужно
//		if (entities.size() == 1)
//		{
//			entities[0]->getComponent<PositionComponent>().position += entities[0]->getComponent<VelocityComponent>().velocity;
//		}

		for (auto it1 = entities.begin(); it1 != entities.end(); it1++)
		{
			if ((*it1)->HasComponent<VelocityComponent>())
			{
                if ((*it1)->HasComponent<MoveDirectionComponent>()) {
                    auto& dir = (*it1)->getComponent<MoveDirectionComponent>();
                    auto& vel = (*it1)->getComponent<VelocityComponent>();

                    if (vel.velocity.x != 0 || vel.velocity.y != 0)
                    {
//                        if ((*it1)->HasComponent<AnimationMovingComponent>())
//                        {
//                            auto& moving = (*it1)->getComponent<AnimationMovingComponent>();
//                            if (!moving.animation_started)
//                            {
//                                moving.animation_started = true;
//                            }
//
//                            std::cout << "Starting animation" << std::endl;
//
//                        }

                        if ((*it1)->HasComponent<FramesComponent>())
                        {
                            auto& framesComponent= (*it1)->getComponent<FramesComponent>();

                            //if (!framesComponent.dying)
                            //{
                                framesComponent.cur_frame_set = FrameSet::MOVE;
                                framesComponent.animation_started = true;
                            //}
                        }

                    }
//                    else
//                    {
//                        if ((*it1)->HasComponent<AnimationMovingComponent>())
//                        {
//                            auto& moving = (*it1)->getComponent<AnimationMovingComponent>();
//                            if (!moving.animation_started)
//                            {
//                                moving.animation_started = false;
//                            }
//
//                            std::cout << "Starting animation" << std::endl;
//
//                        }
//                    }

                    if (vel.velocity.x > 0 && dir.dir == Direction::LEFT || vel.velocity.x < 0 && dir.dir == Direction::RIGHT) {
                        //(*it1)->getComponent<MoveDirectionComponent>().has_dir_changed = true;
                        dir.has_dir_changed = true;
                    }
                    else {
                        //(*it1)->getComponent<MoveDirectionComponent>().has_dir_changed = false;
                        dir.has_dir_changed = false;
                    }

                    if (vel.velocity.x < 0)
                    {
                        dir.dir = Direction::LEFT;
                    }
                    else if (vel.velocity.x > 0)
                    {
                        dir.dir = Direction::RIGHT;
                    }


                }

				Vector2<DistanceValueType> oldPosition = (*it1)->getComponent<PositionComponent>().position;
				(*it1)->getComponent<PositionComponent>().position += (*it1)->getComponent<VelocityComponent>().velocity;

                if ((*it1)->HasComponent<CollisionComponent>())
                {
                    for (auto it2 = entities.begin(); it2 != entities.end(); it2++)
                    {
                        if (it1 != it2 && (*it2)->HasComponent<CollisionComponent>())
                        {

                            (*it1)->getComponent<CollisionComponent>().collisionBox.left = (*it1)->getComponent<PositionComponent>().position.x + (*it1)->getComponent<CollisionComponent>().offset.x;
                            (*it1)->getComponent<CollisionComponent>().collisionBox.top = (*it1)->getComponent<PositionComponent>().position.y +  (*it1)->getComponent<CollisionComponent>().offset.y;
                            (*it2)->getComponent<CollisionComponent>().collisionBox.left = (*it2)->getComponent<PositionComponent>().position.x + (*it2)->getComponent<CollisionComponent>().offset.x;
                            (*it2)->getComponent<CollisionComponent>().collisionBox.top = (*it2)->getComponent<PositionComponent>().position.y  +  (*it2)->getComponent<CollisionComponent>().offset.y;
                            IntRect rect1 = (*it1)->getComponent<CollisionComponent>().collisionBox; //TODO::Might be costly
                            IntRect rect2 = (*it2)->getComponent<CollisionComponent>().collisionBox;

                            if (rect1.intersects(rect2)) {
                                (*it1)->getComponent<PositionComponent>().position = oldPosition;
                                (*it1)->getComponent<VelocityComponent>().velocity = {0, 0};
                                break;
                            }
                        }
                    }
                }
			}
		}

    }

    virtual bool added() override {

        return true; //TODO::find out what to return
    }

    ~MoveSystem() override = default;
 protected:
	bool testCollision(const IntRect &a,const IntRect &b)
	{
		float t;
		if (abs(a.left - b.left) > (a.width + b.width)) return false;
		if (abs(a.top - b.top) > (a.height + b.height)) return false;
		return true;
	}

 private:
    static int ID;
};

#endif //ECS_MOVESYSTEM_H
