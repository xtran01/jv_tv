/*
**    TP CPE Lyon
**    Copyright (C) 2018 Camille FARINEAU / Ahmed LOUDGHIRI / Xuan-Vinh TRAN
**
**    Video Games Module - Sauver le soldat Rohmer
**
**    pnj.cpp
**    Handle the pnj character
*/

#include "pnj.h"

// Default constructor for the pnj character
pnj::pnj()
    : mesh_body(nullptr), body(nullptr)
{
}

/*------------------------------------------------------------------------*\
 * EventReceiver::addPNJMeshToScene
 * Add the mesh to the scene and set the correct position
 *  Param: smgr and textures
 *  Return :
\*------------------------------------------------------------------------*/
void pnj::addPNJMeshToScene(is::ISceneManager *smgr, std::vector<iv::ITexture*> textures){
    // Add the mesh to the scene and add the correct texture
    mesh_body = smgr->getMesh("../data/Warrior/warrior.md2");
    body = smgr->addAnimatedMeshSceneNode(mesh_body);
    body->setMaterialFlag(iv::EMF_LIGHTING, false);
    body->setMaterialTexture(0, textures[8]);
    // Set correct position and declare the prev_position as the current
    body->setPosition(core::vector3df(1317.39,-168.25,-641.06));
    (this)->position_prev = core::vector3df(1317.39,-168.25,-641.06);
    // Set rotation
    body->setRotation(core::vector3df(0.0, -90.0, 0.0));
}

/*------------------------------------------------------------------------*\
 * EventReceiver::addPNJCollider
 * Add the collider to handle the behaviour of the 3d model with the scene
 *  Param: smgr and selector
 *  Return :
\*------------------------------------------------------------------------*/
void pnj::addPNJCollider(is::ISceneManager *smgr, scene::ITriangleSelector *selector){

    // Add a collider that will use the bounding box
    const core::aabbox3d<f32>& box = body -> getBoundingBox();
    core::vector3df radius = 1.2*(box.MaxEdge - box.getCenter());
    scene::ISceneNodeAnimator *anim;
    anim = smgr->createCollisionResponseAnimator(selector,
                                                        body,  // Le noeud que l'on veut gérer
                                                        radius, // "rayons" de la caméra
                                                        ic::vector3df(0, -10, 0),  // gravité
                                                        ic::vector3df(0, -50, 0));  // décalage du centre
    body->addAnimator(anim);
}

/*------------------------------------------------------------------------*\
 * EventReceiver::setAnimation
 * Set the correct animation frames and speed depending on the context
 *  Param: anim (enum of anim)
 *  Return :
\*------------------------------------------------------------------------*/
void pnj::setAnimation(Animation anim)
{
    // Different animation and there frames and speed
    switch(anim)
    {
    case RUN:
        body->setFrameLoop(5,31);
        body->setAnimationSpeed(80.0);
        break;
    case WALK:
        body->setFrameLoop(5,31);

        body->setAnimationSpeed(50.0);
        break;
    case ATTACK:
        body->setFrameLoop(50,78);
        body->setAnimationSpeed(80.0);
        break;
    case DEATH:
        body->setFrameLoop(0,0);
        body->setAnimationSpeed(40.0);
        break;
    case STAND:
        body->setFrameLoop(0,0);
        break;
    }
}

/*------------------------------------------------------------------------*\
 * EventReceiver::follow
 * Handle the behaviour and movement of the pnj character while following the main character
 *  Param: position_character and orientation_character
 *  Return :
\*------------------------------------------------------------------------*/
void pnj::follow(core::vector3df position_character, core::vector3df orientation_character)
{
    // If the main_character has moved
    if((this)->position_prev_character.getDistanceFrom(position_character) > 0.01f)
    {
        // Compute the direction between the position of the pnj character and the new position of the main character
        core::vector3df direction =  (this)->position_prev_character - (this)->position_prev;
        // Compute the distance between the previous position of the main character and the current position of the main character
        float distance = (this)->position_prev_character.getDistanceFrom(position_character);
        // Normalization
        direction.normalize();
        // New position of the pnj character (the weight is used to not put the pnj character at the same location of the main character because there is not collision between them)
        core::vector3df new_pos = position_prev + direction*distance*0.92;
        // Set the new position and rotation
        body->setPosition(new_pos);
        body->setRotation(orientation_character);
        // Save the current position
        (this)->position_prev = new_pos;
    }
}
