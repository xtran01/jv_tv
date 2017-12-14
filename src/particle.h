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
    scene::IParticleSystemSceneNode* ps;
    scene::IParticleEmitter* em;
    //int timer = 30;
public:
    scene::ISceneNode* light;
    scene::IBillboardSceneNode* bill;
    Particle(iv::ITexture *light_texture, iv::ITexture *material_texture);
    Particle();
    void addParticleToScene(is::ISceneManager *smgr, ic::vector3df position_fire, ic::vector3df position_aim);
    void remove();
    void initializeParticle(iv::ITexture *light_texture, iv::ITexture *material_texture);

};

#endif // PARTICLE_H
