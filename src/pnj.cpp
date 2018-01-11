#include "pnj.h"

pnj::pnj()
    : mesh_body(nullptr), body(nullptr)
{
}


void pnj::addPNJMeshToScene(is::ISceneManager *smgr, std::vector<iv::ITexture*> textures){
    mesh_body = smgr->getMesh("../data/Warrior/warrior.md2");
    body = smgr->addAnimatedMeshSceneNode(mesh_body);
    body->setMaterialFlag(iv::EMF_LIGHTING, false);
    body->setMaterialTexture(0, textures[8]);

    body->setPosition(core::vector3df(1317.39,-168.25,-641.06));
    (this)->position_prev = core::vector3df(1317.39,-168.25,-641.06);
    body->setRotation(core::vector3df(0.0, -90.0, 0.0));
}


void pnj::addPNJCollider(is::ISceneManager *smgr, scene::ITriangleSelector *selector){

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


void pnj::setAnimation(Animation anim)
{
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

void pnj::follow(core::vector3df position_character, core::vector3df orientation_character)
{
    if((this)->position_prev_character.getDistanceFrom(position_character) > 0.01f)
    {
        core::vector3df direction =  (this)->position_prev_character - (this)->position_prev;
        float distance = (this)->position_prev_character.getDistanceFrom(position_character);
        direction.normalize();
        core::vector3df new_pos = position_prev + direction*distance*0.92;
        body->setPosition(new_pos);
        body->setRotation(orientation_character);
        (this)->position_prev = new_pos;
    }
}
