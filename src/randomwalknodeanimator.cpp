#include "randomwalknodeanimator.h"

RandomWalkNodeAnimator::RandomWalkNodeAnimator()
{
}


void RandomWalkNodeAnimator::animateNode(irr::scene::ISceneNode *node,irr::u32 timeMs){

    ic::vector3df position = node->getPosition();
    ic::vector3df rotation = node->getRotation();
    //  rotation.rotateXZBy(180,node->getPosition());

    rotation.Y+=0.1;
    node->setRotation(rotation);
    f32 vitesse_deplacement = 0.5f;
    position.X += vitesse_deplacement * cos(rotation.Y * M_PI / 180.0);
    position.Z += -vitesse_deplacement * sin(rotation.Y * M_PI / 180.0);
    node->setPosition(position);




}

irr::scene::ISceneNodeAnimator* RandomWalkNodeAnimator :: createClone(irr::scene::ISceneNode *node,
                                                                      irr::scene::ISceneManager *newManager){
    return NULL;
}

