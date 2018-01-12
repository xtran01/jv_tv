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
/**
 * @brief The Particle class
 */
class Particle
{

    iv::ITexture *light_tex, *material_tex;

    is::IParticleEmitter* em;

public:
    is::ISceneNode* light;
    is::IBillboardSceneNode* bill;
    is::IParticleSystemSceneNode* ps;
    is::IAnimatedMeshSceneNode *fire_particle;
    int frame_time_life = 0;
    /**
     * @brief addParticleToScene : Function adding a particle in the scene
     * @param smgr
     * @param position_fire : Position of the gun (where the particle is supposed to appear first)
     * @param position_aim : Position of the aim (where the particle is supposed to be at the end)
     */
    void addParticleToScene(is::ISceneManager *smgr, ic::vector3df position_fire, ic::vector3df position_aim);
    /**
     * @brief remove : Unshow the particle
     */
    void remove();
    /**
     * @brief initializeParticle : Set the different textures of the particle
     * @param light_texture : Texture of the light
     * @param material_texture : Texture of the material
     */
    void initializeParticle(iv::ITexture *light_texture, iv::ITexture *material_texture);
    /**
     * @brief Particle : Constructor of particle
     */
    Particle();
};

#endif // PARTICLE_H
