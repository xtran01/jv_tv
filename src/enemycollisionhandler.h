#ifndef ENEMYCOLLISIONHANDLER_H
#define ENEMYCOLLISIONHANDLER_H
#include <irrlicht.h>
#include <iostream>


class EnemyCollisionHandler : public irr::scene::ICollisionCallback
{


private:
    irr::core::vector3df previous_resulting_position;

public:
    bool onCollision(const irr::scene::ISceneNodeAnimatorCollisionResponse &animator);

};

#endif // ENEMYCOLLISIONHANDLER_H
