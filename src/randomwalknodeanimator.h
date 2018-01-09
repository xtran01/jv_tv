#ifndef RANDOMWALKNODEANIMATOR_H
#define RANDOMWALKNODEANIMATOR_H
#include <irrlicht.h>


class RandomWalkNodeAnimator : public irr::scene::ISceneNodeAnimator
{
public:
    RandomWalkNodeAnimator();
    void animateNode(irr::scene::ISceneNode *node,irr::u32 timeMs);
    ISceneNodeAnimator* createClone(irr::scene::ISceneNode *node, irr::scene::ISceneManager *newManager);
};

#endif // RANDOMWALKNODEANIMATOR_H
