//
// Created by Lenevo Legion 5 on 04.05.2023.
//

#ifndef ECS_HITBOXSYSTEM_H
#define ECS_HITBOXSYSTEM_H


class HitBoxSystem : BaseSystem {
public:
    virtual void update(EntityManager* entity);

    virtual bool added();

    virtual ~HitBox();
};

#endif //ECS_HITBOXSYSTEM_H
