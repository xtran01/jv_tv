#include "character.h"

/**************************************************************************\
 * Character:Character                                          *
\**************************************************************************/
Character::Character()
    : mesh_body(nullptr), mesh_head(nullptr), mesh_weapon(nullptr), body(nullptr), head(nullptr), weapon(nullptr)
{
}

u32 Character::getReloading_cooldown() const
{
    return reloading_cooldown;
}

u32 Character::getHealth_point() const
{
    return health_point;
}

void Character::addCharacterMeshToScene(is::ISceneManager *smgr, std::vector<iv::ITexture*> textures){


    mesh_body = smgr->getMesh("../data/Chaingunner/chaingunner_body.md2");
    mesh_weapon = smgr->getMesh("../data/Chaingunner/chaingunner_weapon.md2");
    mesh_head = smgr->getMesh("../data/Chaingunner/chaingunner_head.md2");
    mesh_mf = smgr->getMesh("../data/Chaingunner/chaingunner_mf.md2");
    body = smgr->addAnimatedMeshSceneNode(mesh_body);
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

    body->setPosition(core::vector3df(-1596.96, 95.7503, -983.472));
    //body->setPosition(core::vector3df(-79, 156, 265));
    body->setRotation(core::vector3df(0.0, 0.0, 0.0));
}

void Character::addCharacterCollider(is::ISceneManager *smgr, scene::ITriangleSelector *selector){
    const core::aabbox3d<f32>& box = body -> getBoundingBox();
    core::vector3df radius = 1.2*(box.MaxEdge - box.getCenter());
    scene::ISceneNodeAnimator *anim;
    anim = smgr->createCollisionResponseAnimator(selector,
                                                  body,  // Le noeud que l'on veut gérer
                                                  radius, // "rayons" de la caméra
                                                  ic::vector3df(0, -10, 0),  // gravité
                                                  ic::vector3df(0, -32, 0));  // décalage du centre

    body->addAnimator(anim);
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
        body->setFrameLoop(78,110);
        head->setFrameLoop(78,110);
        weapon->setFrameLoop(78,110);

        body->setAnimationSpeed(24.0);
        head->setAnimationSpeed(24.0);
        weapon->setAnimationSpeed(24.0);
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

    if(reloading_cooldown == 0 && munition !=munition_max && stock !=0){
        if (stock >= munition_max-munition-1){
            stock -= (munition_max - munition);
            munition = munition_max;
        }
        if (stock<munition_max && stock+munition <= munition_max){
            munition += stock;
            stock = 0;
        }
        reloading_cooldown = 45;
    }
}

bool Character::is_reloading()
{
    if(reloading_cooldown>0){
        reloading_cooldown--;

        return true;
    }
    return false;

}

void Character::is_invincible(std::vector<iv::ITexture*>& textures)
{
    if(invincibility_frame==1){
        body->setMaterialTexture(0, textures[0]);
        head->setMaterialTexture(0, textures[2]);
        invincibility_frame--;
    }
    if(invincibility_frame>1){
        body->setMaterialTexture(0, textures[5]);
        head->setMaterialTexture(0, textures[6]);
        invincibility_frame--;
    }


}

void Character::take_damage()
{
    if (health_point == 1 && invincibility_frame == 0){
        health_point--;
    }
    else if (health_point>1 && invincibility_frame == 0){
        health_point--;
        invincibility_frame = 50;
    }

}
