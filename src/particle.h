#ifndef PARTICLE_H
#define PARTICLE_H
#include <irrlicht.h>
#include <string>
#include <assert.h>
#include <iostream>

using namespace irr;
namespace is = irr::scene;
namespace iv = irr::video;
namespace ic = irr::core;

class Particle
{
    iv::ITexture *light_tex, *material_tex;
public:
    scene::ISceneNode* light2;
    scene::IBillboardSceneNode* bill;
    Particle(iv::ITexture *light_texture, iv::ITexture *material_texture);
    void addParticleToScene(is::ISceneManager *smgr, ic::vector3df position_fire, ic::vector3df position_aim);
};

#endif // PARTICLE_H
