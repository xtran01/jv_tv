#ifndef RANDOMWALKNODEANIMATOR_H
#define RANDOMWALKNODEANIMATOR_H
#include "constantes.h"
#include <iostream>
using namespace irr;


namespace ic = irr::core;
namespace is = irr::scene;
namespace iv = irr::video;
namespace ig = irr::gui;


class RandomWalkNodeAnimator : public irr::scene::ISceneNodeAnimator
{
private:
    f32 vitesse_run;
    f32 vitesse_walk;
    f32 time_to_change_angle=0;
    f32 time_to_change_sign=0;
    irr::IRandomizer *randomizer;
    irr::f32 plus_or_minus = 1;
public:
    /**
     * @brief RandomWalkNodeAnimator
     * @param vitesse_run_param
     * @param vitesse_walk_param
     * @param rand
     */
    RandomWalkNodeAnimator(f32 vitesse_run_param, f32 vitesse_walk_param,
                           irr::IRandomizer *rand);
    /**
     * @brief animateNode
     * @param node
     * @param timeMs
     */
    void animateNode(irr::scene::ISceneNode *node,irr::u32 timeMs);
    /**
     * @brief createClone
     * @param node
     * @param newManager
     * @return
     */
    ISceneNodeAnimator* createClone(irr::scene::ISceneNode *node, irr::scene::ISceneManager *newManager);

    /**
     * @brief is_following_main_character
     */
    bool is_following_main_character = false;
    /**
     * @brief position_main_character
     */
    ic::vector3df position_main_character;
};

#endif // RANDOMWALKNODEANIMATOR_H
