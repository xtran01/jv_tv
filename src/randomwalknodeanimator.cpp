#include "randomwalknodeanimator.h"

RandomWalkNodeAnimator::RandomWalkNodeAnimator()
{
}


void RandomWalkNodeAnimator::animateNode(irr::scene::ISceneNode *node,irr::u32 timeMs){

    ic::vector3df position = node->getPosition();
    ic::vector3df rotation = node->getRotation();

    if(!is_following_main_character){
        //random walk
        rotation.Y+=0.2;
        node->setRotation(rotation);
        f32 vitesse_deplacement = 0.5f;
        position.X += vitesse_deplacement * cos(rotation.Y * M_PI / 180.0);
        position.Z += -vitesse_deplacement * sin(rotation.Y * M_PI / 180.0);
        node->setPosition(position);
    }
    else {

    }
}

irr::scene::ISceneNodeAnimator* RandomWalkNodeAnimator :: createClone(irr::scene::ISceneNode *node,
                                                                      irr::scene::ISceneManager *newManager){
    return NULL;
}

