#ifndef CHARACTER_H
#define CHARACTER_H
#include <irrlicht.h>
#include <string>
#include <assert.h>
#include <iostream>
/*
**    TP CPE Lyon
**    Copyright (C) 2018 Camille FARINEAU / Ahmed LOUDGHIRI / Xuan-Vinh TRAN
**
**    Video Games Module - Sauver le soldat Rohmer
**
**    character.h
**    Handle the main character
*/

#include <vector>

using namespace irr;
namespace is = irr::scene;
namespace iv = irr::video;
namespace ic = irr::core;
/**
 * @brief The Character class
 */
class Character
{
private:

    //Mesh associated to the enemy
    is::IAnimatedMesh *mesh_body;
    is::IAnimatedMesh *mesh_head;
    is::IAnimatedMesh *mesh_weapon;
    is::IAnimatedMesh *mesh_mf;
    u32 munition_max = 20;

    u32 munition = 20;
    u32 stock = 90;
    u32 health_point = 30;
    u32 reloading_cooldown = 0;
    u32 invincibility_frame = 0;

public:
    /**
     * @brief The Animation enum contains all the different action possible for the Character
     */
    enum Animation { RUN, WALK, ATTACK, DEATH, STAND };
    /**
     * @brief body : Noeud qui mermet de manipuler le maillage
     */
    is::IAnimatedMeshSceneNode *body;
    /**
     * @brief head : Head Node
     */
    is::IAnimatedMeshSceneNode *head;
    /**
     * @brief weapon : Weapon Node
     */
    is::IAnimatedMeshSceneNode *weapon;
    /**
     * @brief mf : mf Node
     */
    is::IAnimatedMeshSceneNode *mf;

    /**
     * @brief addCharacterMeshToScene : Add the Character to the scene
     * @param smgr : pointer to the scene manager
     * @param tex : Texture array containing all the textures needed (body, head, weapon, mf)
     */
    void addCharacterMeshToScene(is::ISceneManager *smgr, std::vector<video::ITexture *> tex);
    /**
     * @brief addCharacterCollider : Add a collision box to the character
     * @param smgr : pointer to the scene manager
     * @param selector :
     */
    void addCharacterCollider(is::ISceneManager *smgr, scene::ITriangleSelector *selector);
    /**
     * @brief setAnimation : Set the animation of the character
     * @param anim : One of animation of the enum
     */
    void setAnimation(Animation anim);
    /**
     * @brief change_texture_weapon_fire: Set the fire animation of the gun from the texture array
     * @param textures : Texture array containing all the textures needed (body, head, weapon, mf)
     */
    void change_texture_weapon_fire(std::vector<iv::ITexture*>& textures);
    /**
     * @brief change_texture_weapon_rest : Set the rest animation of the gun from the texture array
     * @param textures : Texture array containing all the textures needed (body, head, weapon, mf)
     */
    void change_texture_weapon_rest(std::vector<iv::ITexture*>& textures);
    /**
     * @brief get_nb_stock : Get the number of munition in stock remaining
     * @return the stock
     */
    u32 get_nb_stock()const;
    /**
     * @brief get_nb_munition : Get the number of munition in cartridge remaining
     * @return the munition
     */
    u32 get_nb_munition()const;
    /**
     * @brief use_munition : Decrement the number of munition by 1
     */
    void use_munition();
    /**
     * @brief reload : Take ammo in the sotck to the cartridge
     */
    void reload();
    /**
     * @brief is_reloading : Decrement the reloading_cooldown
     * @return  true if the character is reloading (if reloading_cooldown > 0)
     */
    bool is_reloading();

    /**
     * @brief is_invincible : Decrement the invincibility_frame
     * @param textures : textures applied when the charater is invincible or not
     */
    void is_invincible(std::vector<iv::ITexture*>& textures);
    /**
     * @brief take_damage : Reduce the health_point if the character is not invincible
     */
    void take_damage();

    /**
     * @brief getReloading_cooldown : Getter
     * @return reloading_cooldown
     */
    u32 getReloading_cooldown() const;
    /**
     * @brief getHealth_point : Getter
     * @return health_point
     */
    u32 getHealth_point() const;

    /**
     * @brief Character : Default constructor
     */
    Character();

};
#endif // CHARACTER_H
