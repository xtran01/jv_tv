#ifndef PNJ_H
#define PNJ_H

#include <irrlicht.h>
#include <string>
#include <assert.h>
#include <iostream>
#include <vector>
#include "character.h"

using namespace irr;
namespace is = irr::scene;
namespace iv = irr::video;
namespace ic = irr::core;

class pnj
{
private:

    /**
      * @brief smgr : pointer to the scene manager
      */
     is::ISceneManager *smgr;
     /**
     * @brief mesh : Mesh associated to the enemy
     */
    is::IAnimatedMesh * mesh;

    /**
    * @brief node : Node of the enemy
    */
    is::IAnimatedMesh *mesh_body;


    core::vector3df position_prev;

public:
    /**
     * @brief The Animation enum contains all the different action possible for the Character
     */
    enum Animation { RUN, WALK, ATTACK, DEATH, STAND };
    core::vector3df position_prev_character;
    /**
     * @brief body : Noeud qui mermet de manipuler le maillage
     */
    is::IAnimatedMeshSceneNode *body;

    u32 health_point = 3;
    /**
     * @brief addPNJMeshToScene
     */
    void addPNJMeshToScene(is::ISceneManager *smgr, std::vector<iv::ITexture*> textures);
    /**
     * @brief setPosition : Set the position of the enemy
     * @param vec3 : New position of the mesh
     */
    //void setPosition(ic::vector3df vec3);
    /**
     * @brief create_collision_with_map
     * @param world
     */
    //void create_collision_with_map(is::ITriangleSelector *world);
    /**
     * @brief addCharacterCollider : Add a collision box to the character
     * @param smgr : pointer to the scene manager
     * @param selector :
     */
    void addPNJCollider(is::ISceneManager *smgr, scene::ITriangleSelector *selector);
    /**
     * @brief setAnimation : Set the animation of the character
     * @param anim : One of animation of the enum
     */
    void setAnimation(Animation anim);
    /**
     * @brief meeting: look if the character has joined the PNJ
     * @param smgr
     */
    void follow(core::vector3df position_character, core::vector3df orientation_character);
    /**
     * @brief pnj : Default constructor
     */
    pnj();

};

#endif // PNJ_H
