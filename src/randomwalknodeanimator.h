#ifndef RANDOMWALKNODEANIMATOR_H
#define RANDOMWALKNODEANIMATOR_H
#include <irrlicht.h>


class RandomWalkNodeAnimator : public irr::scene::ISceneNodeAnimator
{
public:
    RandomWalkNodeAnimator();
    virtual void animateNode(irr::scene::ISceneNode *node,irr::u32 timeMs);
};

#endif // RANDOMWALKNODEANIMATOR_H
