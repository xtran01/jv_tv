#include "character.h"

/**************************************************************************\
 * Character:Character                                          *
\**************************************************************************/
Character::Character()
    : mesh_body(nullptr), mesh_head(nullptr), mesh_weapon(nullptr), body(nullptr), head(nullptr), weapon(nullptr)
{
}

void Character::addCharacterMeshToScene(is::ISceneManager *smgr, std::vector<iv::ITexture*> textures){


    mesh_body = smgr->getMesh("../data/Chaingunner/chaingunner_body.md2");
    mesh_weapon = smgr->getMesh("../data/Chaingunner/chaingunner_weapon.md2");
    mesh_head = smgr->getMesh("../data/Chaingunner/chaingunner_head.md2");
    mesh_mf = smgr->getMesh("../data/Chaingunner/chaingunner_mf.md2");
    body = smgr->addAnimatedMeshSceneNode(mesh_body,0,-1);
    weapon = smgr->addAnimatedMeshSceneNode(mesh_weapon,body,-1,core::vector3df(0,0,0),core::vector3df(0,0,0));
    head = smgr->addAnimatedMeshSceneNode(mesh_head,body,-1,core::vector3df(0,0,0),core::vector3df(0,0,0));
    mf = smgr->addAnimatedMeshSceneNode(mesh_mf,body,-1,core::vector3df(0,0,0),core::vector3df(0,0,0));

    body->setMaterialFlag(iv::EMF_LIGHTING, false);
    weapon->setMaterialFlag(iv::EMF_LIGHTING, false);
    head->setMaterialFlag(iv::EMF_LIGHTING, false);
    mf->setMaterialFlag(iv::EMF_LIGHTING, false);

    body->setMaterialTexture(0, textures[0]);
    weapon->setMaterialTexture(0, textures[1]);
    head->setMaterialTexture(0, textures[2]);
    mf->setMaterialTexture(0, textures[4]);

    mf->setVisible(false);
}

void Character::addCharacterCollider(is::ISceneManager *smgr, scene::ITriangleSelector *selector){
    const core::aabbox3d<f32>& box = body -> getBoundingBox();
    core::vector3df radius = 1.2*(box.MaxEdge - box.getCenter());
    scene::ISceneNodeAnimator *anim;
    anim = smgr->createCollisionResponseAnimator(selector,
                                                  body,  // Le noeud que l'on veut gérer
                                                  radius, // "rayons" de la caméra
                                                  ic::vector3df(0, -10, 0),  // gravité
                                                  ic::vector3df(0, 0, 0));  // décalage du centre

    body->addAnimator(anim);
}

Character::Character(is::ISceneManager *smgr)
{
    mesh_body = smgr->getMesh("../data/tris.md2");
}

void Character::setAnimation(Animation anim)
{
    switch(anim)
    {
    case RUN:
        body->setFrameLoop(5,31);
        head->setFrameLoop(5,31);
        weapon->setFrameLoop(5,31);

        body->setAnimationSpeed(80.0);
        head->setAnimationSpeed(80.0);
        weapon->setAnimationSpeed(80.0);
        break;
    case WALK:
        body->setFrameLoop(5,31);
        head->setFrameLoop(5,31);
        weapon->setFrameLoop(5,31);

        body->setAnimationSpeed(50.0);
        head->setAnimationSpeed(50.0);
        weapon->setAnimationSpeed(50.0);
        break;
    case ATTACK:
        body->setFrameLoop(50,78);
        head->setFrameLoop(50,78);
        weapon->setFrameLoop(50,78);

        body->setAnimationSpeed(80.0);
        head->setAnimationSpeed(80.0);
        weapon->setAnimationSpeed(80.0);
        break;
    case DEATH:
        body->setFrameLoop(0,0);
        head->setFrameLoop(0,0);
        weapon->setFrameLoop(0,0);

        body->setAnimationSpeed(40.0);
        head->setAnimationSpeed(40.0);
        weapon->setAnimationSpeed(40.0);
        break;
    case STAND:
        body->setFrameLoop(0,0);
        head->setFrameLoop(0,0);
        weapon->setFrameLoop(0,0);
        break;
    }
}

void Character::change_texture_weapon_fire(std::vector<iv::ITexture*>& textures)
{
    weapon->setMaterialTexture(0, textures[3]);
}
void Character::change_texture_weapon_rest(std::vector<iv::ITexture*>& textures)
{
    weapon->setMaterialTexture(0, textures[1]);
}

u32 Character::get_nb_stock() const
{
    return stock;
}

u32 Character::get_nb_munition() const
{
    return munition;
}

void Character::use_munition()
{
    munition--;
}
void Character::reload()
{
    if (stock >= 10-munition-1 && stock !=0){
        stock -= (10 - munition);
        munition = 10;
    }


}
