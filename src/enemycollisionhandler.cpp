#include "enemycollisionhandler.h"

void display_vector(ic::vector3df vec){
    std::cout<<"("<<vec.X<<","<<vec.Y<<","<<vec.Z<<")"<<std::endl;
}

/**
 * onCollision
 * ***********
 * called every time there is a collision with the map
 * Each time there is a collision we detect if it's with a wall
 * Then we turn the enemy node with a rotation of 180
 * @brief EnemyCollisionHandler::onCollision
 * @param animator
 * @return
 */
bool EnemyCollisionHandler::onCollision(
        const irr::scene::ISceneNodeAnimatorCollisionResponse &animator){
    //Node associated to the enmy colliding
    is::ISceneNode *node_associated =  animator.getTargetNode();

    const irr::f32 epsilon = 0.2;

    //Irrlicht calculate new position automaticaly when there is a collision
    // Here we grab the calculated position
    ic::vector3df new_calculated_pos = animator.getCollisionResultPosition();

    //we get the distance to the previous calcul
    irr::f32 distance = new_calculated_pos.getDistanceFrom(previous_calculated_pos);


    //If the distance is < to the vitesse of walking => enemy stuck
    if(distance < WALK_VITESSE_ENEMY - epsilon ){
        //collision with wall
        //We turn the node associated with a rotation of 180 degrees
        ic::vector3df node_rotation = node_associated->getRotation();
        node_rotation.Y += 180;
        node_associated->setRotation(node_rotation);
        ic::vector3df node_position = node_associated->getPosition();

        //we move the enemy rotated previously
        node_position += WALK_VITESSE_ENEMY * cos(node_rotation.Y * M_PI / 180.0);
        node_position += -WALK_VITESSE_ENEMY * sin(node_rotation.Y * M_PI / 180.0);
        node_associated->setPosition(node_position);
        previous_calculated_pos = node_position;
        return false;
    }
    else{
        node_associated->setPosition(new_calculated_pos);
        previous_calculated_pos = new_calculated_pos;
        return false;
    }
}


