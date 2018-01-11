#include "randomwalknodeanimator.h"

RandomWalkNodeAnimator::RandomWalkNodeAnimator(f32 vitesse_run_param, f32 vitesse_walk_param)
{
    vitesse_run =  vitesse_run_param;
    vitesse_walk = vitesse_walk_param;
}


void RandomWalkNodeAnimator::animateNode(irr::scene::ISceneNode *node,irr::u32 timeMs){

    std::cout<<"time: "<<timeMs<<std::endl;
    ic::vector3df position = node->getPosition();
    ic::vector3df rotation = node->getRotation();

    if(!is_following_main_character){

//            f32 radius = 100.f;
//            ic::array<ic::vector3df> points;
//           for(int i = 0; i< 10; i++){
//                f32 r = random_generator->frand() * radius;
//                f32 teta = random_generator->frand() * M_PI * 2.0f;
//                f32 test = random_generator->frand();
//                ic::vector3df position = waiting_position_center;
//                position.X += r*cos(teta);
//                position.Z += r*sin(teta);
//               points.push_back(position);

        //random walk
        rotation.Y+=0.2;
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

