/*
**    TP CPE Lyon
**    Copyright (C) 2018 Camille FARINEAU / Ahmed LOUDGHIRI / Xuan-Vinh TRAN
**
**    Video Games Module - Sauver le soldat Rohmer
**
**    character.cpp
**    Handle the main character
*/

#include "character.h"

/**************************************************************************\
 * Character:Character                                                    *
\**************************************************************************/
Character::Character()
    : mesh_body(nullptr), mesh_head(nullptr), mesh_weapon(nullptr), body(nullptr), head(nullptr), weapon(nullptr)
{
}

/*------------------------------------------------------------------------*\
 * Character::getReloading_cooldown
 * Get the cooldown of the reloading
 *  Param:
 *  Return :
\*------------------------------------------------------------------------*/
u32 Character::getReloading_cooldown() const
{
    return reloading_cooldown;
}

/*------------------------------------------------------------------------*\
 * Character::getHealth_point
 * Get health point
 *  Param:
 *  Return :
\*------------------------------------------------------------------------*/
u32 Character::getHealth_point() const
{
    return health_point;
}

/*------------------------------------------------------------------------*\
 * Character::addCharacterMeshToScene
 * Add the meshes to the scene and set the correct position
 *  Param:
 *  Return :
\*------------------------------------------------------------------------*/
void Character::addCharacterMeshToScene(is::ISceneManager *smgr, std::vector<iv::ITexture*> textures){

    // Add the meshes to the scene and add the correct texture - for all the part of the main character
    mesh_body = smgr->getMesh("../data/Chaingunner/chaingunner_body.md2");
    mesh_weapon = smgr->getMesh("../data/Chaingunner/chaingunner_weapon.md2");
    mesh_head = smgr->getMesh("../data/Chaingunner/chaingunner_head.md2");
    mesh_mf = smgr->getMesh("../data/Chaingunner/chaingunner_mf.md2");
    // The weapon, head and mf are children of the body node. They will all move as the body move
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

    // mf is corresponding to the mesh of the explosion at the end of the weapon
    mf->setVisible(false);

    // Set the correct position and rotation for the main_character
    body->setPosition(core::vector3df(-1596.96, 95.7503, -983.472));
    body->setRotation(core::vector3df(0.0, 0.0, 0.0));
}

/*------------------------------------------------------------------------*\
 * Character::addCharacterCollider
 * Add the collider to the node of the main character
 *  Param:
 *  Return :
\*------------------------------------------------------------------------*/
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

/*------------------------------------------------------------------------*\
 * Character::setAnimation
 * Set the proper animation (frame loop and speed) depending on the context
 *  Param: anim
 *  Return :
\*------------------------------------------------------------------------*/
void Character::setAnimation(Animation anim)
{
    // Different animation depending on the context
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

/*------------------------------------------------------------------------*\
 * Character::change_texture_weapon_fire
 * Change the texture of the weapon when the character is attacking
 *  Param: textures
 *  Return :
\*------------------------------------------------------------------------*/
void Character::change_texture_weapon_fire(std::vector<iv::ITexture*>& textures)
{
    weapon->setMaterialTexture(0, textures[3]);
}
/*------------------------------------------------------------------------*\
 * Character::change_texture_weapon_rest
 * Change the texture of the weapon when the character is not attacking
 *  Param:
 *  Return :
\*------------------------------------------------------------------------*/
void Character::change_texture_weapon_rest(std::vector<iv::ITexture*>& textures)
{
    weapon->setMaterialTexture(0, textures[1]);
}
/*------------------------------------------------------------------------*\
 * Character::get_nb_stock
 * Get the number of bullet in stock
 *  Param:
 *  Return :
\*------------------------------------------------------------------------*/
u32 Character::get_nb_stock() const
{
    return stock;
}
/*------------------------------------------------------------------------*\
 * Character::get_nb_munition
 * Change the number of munition in the cartridge
 *  Param:
 *  Return :
\*------------------------------------------------------------------------*/
u32 Character::get_nb_munition() const
{
    return munition;
}
/*------------------------------------------------------------------------*\
 * Character::use_munition
 * Decrement the number of ammunition
 *  Param:
 *  Return :
\*------------------------------------------------------------------------*/
void Character::use_munition()
{
    munition--;
}
/*------------------------------------------------------------------------*\
 * Character::reload
 * Function to reload : update the number of ammo in cartridge and in stock
 *  Param:
 *  Return :
\*------------------------------------------------------------------------*/
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
/*------------------------------------------------------------------------*\
 * Character::is_reloading
 * Update the cooldown for the reloading phase : to reload it will take some frame
 *  Param:
 *  Return :
\*------------------------------------------------------------------------*/
bool Character::is_reloading()
{
    if(reloading_cooldown>0){
        reloading_cooldown--;

        return true;
    }
    return false;

}
/*------------------------------------------------------------------------*\
 * Character::is_invincible
 * Set the correct textures and decrement the counter for the invincibility frame
 * After the character has been hit there is a few frame where it is unvunerable
 *  Param:
 *  Return :
\*------------------------------------------------------------------------*/
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
/*------------------------------------------------------------------------*\
 * Character::take_damage
 * Update the health point of the character if it has been hit
 *  Param:
 *  Return :
\*------------------------------------------------------------------------*/
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
