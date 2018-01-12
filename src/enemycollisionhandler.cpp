#include "enemycollisionhandler.h"


void display_vector(ic::vector3df vec){
    std::cout<<"("<<vec.X<<","<<vec.Y<<","<<vec.Z<<")"<<std::endl;
}

bool EnemyCollisionHandler::onCollision(
        const irr::scene::ISceneNodeAnimatorCollisionResponse &animator){
    is::ISceneNode *node_associated =  animator.getTargetNode();

    const irr::f32 epsilon = 0.1;
    ic::vector3df new_calculated_pos = animator.getCollisionResultPosition();

    irr::f32 distance = new_calculated_pos.getDistanceFrom(previous_calculated_pos);

    previous_calculated_pos = new_calculated_pos;

    if(distance < WALK_VITESSE_ENEMY - epsilon ){
        //collision with wall
        //We turn the node associated with a rotation of 180 degrees
        ic::vector3df node_rotation = node_associated->getRotation();
        node_rotation.Y += 180;
        node_associated->setRotation(node_rotation);
        ic::vector3df node_position = node_associated->getPosition();
        node_position += WALK_VITESSE_ENEMY * cos(node_rotation.Y * M_PI / 180.0);
        node_position += -WALK_VITESSE_ENEMY * sin(node_rotation.Y * M_PI / 180.0);
        node_associated->setPosition(node_position);

    }
}


