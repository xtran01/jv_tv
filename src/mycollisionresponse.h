#ifndef MYCOLLISIONRESPONSE_H
#define MYCOLLISIONRESPONSE_H
#include <irrlicht.h>
#include <iostream>

class MyCollisionResponse : public irr::scene::ICollisionCallback
{
public:
    MyCollisionResponse();
    bool onCollision(const irr::scene::ISceneNodeAnimatorCollisionResponse &animator);
};

#endif // MYCOLLISIONRESPONSE_H
