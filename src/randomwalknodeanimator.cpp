#include "randomwalknodeanimator.h"

RandomWalkNodeAnimator::RandomWalkNodeAnimator(f32 vitesse_run_param, f32 vitesse_walk_param,
                                               irr::IRandomizer *rand)
{
    vitesse_run =  vitesse_run_param;
    vitesse_walk = vitesse_walk_param;
    randomizer =rand;
}


void RandomWalkNodeAnimator::animateNode(irr::scene::ISceneNode *node,irr::u32 timeMs){

    ic::vector3df position = node->getPosition();
    ic::vector3df rotation = node->getRotation();

    if(time_to_change_sign > 15){
        time_to_change_sign = 0;
        if(floor(2 * randomizer->frand() - 1) == 0){
            plus_or_minus =1;
        }
        else{
            plus_or_minus = -1;
        }
    }


    if(time_to_change_angle > TIME_BEFORE_CHANGING_RANDOM_WALK_DIRECTION){
        //change direction of walking
        time_to_change_angle = 0;
        rotation.Y = randomizer->frand() * 60;
    }
    time_to_change_angle ++;
    time_to_change_sign++;

    if(!is_following_main_character){
        //random walk


        rotation.Y+= plus_or_minus * 1.1;
        node->setRotation(rotation);

        position.X += vitesse_walk * cos(rotation.Y * M_PI / 180.0);
        position.Z += -vitesse_walk * sin(rotation.Y * M_PI / 180.0);
        node->setPosition(position);
    }
    else {
        //follow main character
        ic::vector3df enemy_to_main = position_main_character - position; // vector from enemy to main character
        enemy_to_main = enemy_to_main.normalize(); // vector normalized

        /*
         * handle the angle of rotation to look at enemy
         * */
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

