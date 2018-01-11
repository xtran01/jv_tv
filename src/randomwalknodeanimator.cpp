#include "randomwalknodeanimator.h"

RandomWalkNodeAnimator::RandomWalkNodeAnimator(f32 vitesse_run_param, f32 vitesse_walk_param)
{
    vitesse_run =  vitesse_run_param;
    vitesse_walk = vitesse_walk_param;
}


void RandomWalkNodeAnimator::animateNode(irr::scene::ISceneNode *node,irr::u32 timeMs){

    ic::vector3df position = node->getPosition();
    ic::vector3df rotation = node->getRotation();

    if(!is_following_main_character){
        //random walk
        rotation.Y+=0.2;
        node->setRotation(rotation);

        position.X += vitesse_walk * cos(rotation.Y * M_PI / 180.0);
        position.Z += -vitesse_walk * sin(rotation.Y * M_PI / 180.0);
        node->setPosition(position);
    }
    else {
        //follow main character
        ic::vector3df enemy_to_main = position_main_character - position;
        enemy_to_main = enemy_to_main.normalize();
        f32 angle = 0;
        if(enemy_to_main.X >=0 && enemy_to_main.Z >= 0){
            angle = acos(enemy_to_main.Z);
            angle = (3 * M_PI_2) + angle;
        }
        else if(enemy_to_main.X>=0 && enemy_to_main.Z <=0){
             angle = acos(enemy_to_main.X);
        }
        else if(enemy_to_main.X <=0 && enemy_to_main.Z >=0){
             angle = acos(enemy_to_main.Z);
             angle = 3*M_PI_2 - angle;
        }
        else{
             angle = acos(-enemy_to_main.Z);
             angle = M_PI_2 + angle;
        }


        position+= vitesse_run * enemy_to_main;
        rotation.Y=(angle * 180.0f) / M_PI ;
        node->setRotation(rotation);
        node->setPosition(position);
    }
}

irr::scene::ISceneNodeAnimator* RandomWalkNodeAnimator :: createClone(irr::scene::ISceneNode *node,
                                                                      irr::scene::ISceneManager *newManager){
    return NULL;
}

