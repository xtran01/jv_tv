#include "character.h"

void Character::addCharacterMeshToScene(is::ISceneManager *smgr, iv::ITexture *tex){
    node = smgr->addAnimatedMeshSceneNode(mesh);
    node -> setMaterialFlag(irr::video::EMF_LIGHTING,false);
    node -> setMD2Animation(irr::scene::EMAT_STAND);
    node -> setMaterialTexture(0, tex);
    node -> setPosition(ic::vector3df(0, 0, 0));
}

void Character::addCharacterCollider(is::ISceneManager *smgr, scene::ITriangleSelector *selector){
    const core::aabbox3d<f32>& box = node -> getBoundingBox();
    core::vector3df radius = 1.2*(box.MaxEdge - box.getCenter());
    scene::ISceneNodeAnimator *anim;
    anim = smgr->createCollisionResponseAnimator(selector,
                                                  node,  // Le noeud que l'on veut gérer
                                                  radius, // "rayons" de la caméra
                                                  ic::vector3df(0, -10, 0),  // gravité
                                                  ic::vector3df(0, -10, 0));  // décalage du centre

    node->addAnimator(anim);
}

Character::Character(is::ISceneManager *smgr)
{
    mesh = smgr->getMesh("../data/tris.md2");
}
