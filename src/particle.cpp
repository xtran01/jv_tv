#include "particle.h"
/*------------------------------------------------------------------------*\
 * Particle::Particle
 * Default Constructor
\*------------------------------------------------------------------------*/
Particle::Particle()
{

}
/*------------------------------------------------------------------------*\
 * Particle::initializeParticle(iv::ITexture *light_texture, iv::ITexture *material_texture)
 * Set the correct textures to the light and material used
 * Param : One texture for the light and one for the material
\*------------------------------------------------------------------------*/
void Particle::initializeParticle(iv::ITexture *light_texture, iv::ITexture *material_texture){
    light_tex=(light_texture);
    material_tex=(material_texture);
}

/*------------------------------------------------------------------------*\
 * Particle::remove()
 * Hide the billboard and the particle system
\*------------------------------------------------------------------------*/
void Particle::remove()
{
    bill->setVisible((false));
    ps->setVisible((false));
}
/*------------------------------------------------------------------------*\
 * Particle::addParticleToScene(is::ISceneManager *smgr, ic::vector3df position_fire, ic::vector3df position_aim)
 * Add a particle to a scene, set a time_life to the particle, set the material texture
 * Set the straight animation to the light
 * Param : Scene Manager / Initial position of the light / Aim Position
\*------------------------------------------------------------------------*/
void Particle::addParticleToScene(is::ISceneManager *smgr, ic::vector3df position_fire, ic::vector3df position_aim){

    frame_time_life = 30;
    light = smgr->addLightSceneNode(0, core::vector3df(0,0,0),
                                    video::SColorf(1.0f, 0.2f, 0.2f, 0.0f), 300.0f);
    bill = smgr->addBillboardSceneNode(light, core::dimension2d<f32>(10, 10));
    bill->setMaterialFlag(video::EMF_LIGHTING, false);
    bill->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
    bill->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
    bill->setMaterialTexture(0, light_tex);
    // add fly straight animator to light
    is::ISceneNodeAnimator *anim = smgr->createFlyStraightAnimator(position_fire,
                                                                   position_aim, position_fire.getDistanceFrom(position_aim)/2.5f,false,false);

    light->addAnimator(anim);
    anim->drop(); //Drop the anim not used anymore

    // add particle system
    ps = smgr->addParticleSystemSceneNode(false, light);
    // create and set emitter
    em = ps->createBoxEmitter(
                core::aabbox3d<f32>(-3,0,-3,3,1,3),
                core::vector3df(0.0f,0.03f,0.0f),
                80,100,
                video::SColor(10,255,255,255), video::SColor(10,255,255,255),
                400,1100);
    // Size of the emitter at the beginning and at the end
    em->setMinStartSize(core::dimension2d<f32>(8.0f, 11.0f));
    em->setMaxStartSize(core::dimension2d<f32>(8.0f, 11.0f));

    ps->setEmitter(em);
    em->drop();

    // create and set affector
    scene::IParticleAffector* paf = ps->createFadeOutParticleAffector();
    ps->addAffector(paf);
    paf->drop();

    // adjust some material settings
    ps->setMaterialFlag(video::EMF_LIGHTING, false);
    ps->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
    ps->setMaterialTexture(0, material_tex);
    ps->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);


}
