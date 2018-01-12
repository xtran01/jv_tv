/*
**    TP CPE Lyon
**    Copyright (C) 2018 Camille FARINEAU / Ahmed LOUDGHIRI / Xuan-Vinh TRAN
**
**    Video Games Module - Sauver le soldat Rohmer
**
**    pnj.h
**    Handle the pnj character
*/

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
     * @brief mesh : Mesh associated to the pnj character
     */
    is::IAnimatedMesh * mesh;

    /**
    * @brief node : Node of the pnj character
    */
    is::IAnimatedMesh *mesh_body;

    /**
    * @brief position_prev: previous position of the pnj character
    */
    core::vector3df position_prev;

public:
    /**
     * @brief The Animation enum contains all the different action possible for the Character
     */
    enum Animation { RUN, WALK, ATTACK, DEATH, STAND };
    /**
     * @brief position_prev_character : Previous position of the main character
     */
    core::vector3df position_prev_character;
    /**
     * @brief body : node to handl mesh of the body
     */
    is::IAnimatedMeshSceneNode *body;
    /**
     * @brief addPNJMeshToScene
     */
    void addPNJMeshToScene(is::ISceneManager *smgr, std::vector<iv::ITexture*> textures);
    /**
     * @brief addPNJCollider : Add a collision box to the pnj character
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
     * @brief follow: handle the movement of the pnj character if it is following the main character
     * @param smgr
     */
    void follow(core::vector3df position_character, core::vector3df orientation_character);
    /**
     * @brief pnj : Default constructor
     */
    pnj();

};

#endif // PNJ_H
