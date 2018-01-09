#include "randomwalknodeanimator.h"

RandomWalkNodeAnimator::RandomWalkNodeAnimator()
{
}

namespace scene {
void RandomWalkNodeAnimator::animateNode(irr::scene::ISceneNode *node,irr::u32 timeMs){
  irr::core::vector3df position = node->getPosition();
  position.X += 1.0f;
  node->setPosition(position);
}
}
