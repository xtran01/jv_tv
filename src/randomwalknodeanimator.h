#ifndef RANDOMWALKNODEANIMATOR_H
#define RANDOMWALKNODEANIMATOR_H
#include <irrlicht.h>
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
    f32 time_to_change=0;
    irr::IRandomizer *randomizer;
    f32 angle_rotation;
public:
    RandomWalkNodeAnimator(f32 vitesse_run_param, f32 vitesse_walk_param,
                           irr::IRandomizer *rand);
    void animateNode(irr::scene::ISceneNode *node,irr::u32 timeMs);
    ISceneNodeAnimator* createClone(irr::scene::ISceneNode *node, irr::scene::ISceneManager *newManager);
    bool is_following_main_character = false;
    ic::vector3df position_main_character;
};

#endif // RANDOMWALKNODEANIMATOR_H
