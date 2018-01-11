#ifndef CHARACTER_H
#define CHARACTER_H
#include <irrlicht.h>
#include <string>
#include <assert.h>
#include <iostream>
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
     * @brief Character : Default constructor
     */
    Character();
};
#endif // CHARACTER_H
