#include "particle.h"

Particle::Particle()
{
}
void Particle::addParticleToScene(is::ISceneManager *smgr){
    node = smgr->addAnimatedMeshSceneNode(mesh);
    node -> setMaterialFlag(irr::video::EMF_LIGHTING,false);
    node -> setMD2Animation(irr::scene::EMAT_STAND);
}
