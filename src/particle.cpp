#include "particle.h"

Particle::Particle(iv::ITexture *light_texture, iv::ITexture *material_texture):light_tex(light_texture),material_tex(material_texture)
{


}

void Particle::addParticleToScene(is::ISceneManager *smgr, ic::vector3df position_fire, ic::vector3df position_aim){

    light2 =smgr->addLightSceneNode(0, core::vector3df(0,0,0),
                                    video::SColorf(1.0f, 0.2f, 0.2f, 0.0f), 800.0f);
    bill = smgr->addBillboardSceneNode(light2, core::dimension2d<f32>(120, 120));
    bill->setMaterialFlag(video::EMF_LIGHTING, false);
    bill->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
    bill->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
    bill->setMaterialTexture(0, light_tex);
    // add fly circle animator to light 2
    is::ISceneNodeAnimator *anim = smgr->createFlyStraightAnimator(position_fire,
                                                                   position_aim, 3000,false,false);

    light2->addAnimator(anim);
    anim->drop();

    // add particle system
    scene::IParticleSystemSceneNode* ps =
            smgr->addParticleSystemSceneNode(false, light2);
    // create and set emitter
    scene::IParticleEmitter* em = ps->createBoxEmitter(
                core::aabbox3d<f32>(-3,0,-3,3,1,3),
                core::vector3df(0.0f,0.03f,0.0f),
                80,100,
                video::SColor(10,255,255,255), video::SColor(10,255,255,255),
                400,1100);
    em->setMinStartSize(core::dimension2d<f32>(30.0f, 40.0f));
    em->setMaxStartSize(core::dimension2d<f32>(30.0f, 40.0f));

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
