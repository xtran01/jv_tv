#include "enemycollisionhandler.h"




bool EnemyCollisionHandler::onCollision(
        const irr::scene::ISceneNodeAnimatorCollisionResponse &animator){
    irr::f32 distance_to_previous_position = animator.getCollisionResultPosition()
            .getDistanceFrom(previous_resulting_position);
    is::ISceneNode *node_associated =  animator.getTargetNode();
    //collision with wall
    if(distance_to_previous_position < 0.3f){
        //We turn the node associated with a rotation of 180 degrees
        ic::vector3df node_rotation = node_associated->getRotation();
        node_rotation.Y += 180;
        node_associated->setRotation(node_rotation);
    }
    else{
        previous_resulting_position = animator.getCollisionResultPosition();
    }

}


