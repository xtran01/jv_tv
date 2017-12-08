#include "mycollisionresponse.h"

MyCollisionResponse::MyCollisionResponse()
{
}

bool MyCollisionResponse::onCollision(
        const irr::scene::ISceneNodeAnimatorCollisionResponse &animator){
    std::cout<<"COLLISION"<<std::endl;

}
