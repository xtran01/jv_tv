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

class Character
{
private:
    //Mesh associated to the enemy
    is::IAnimatedMesh *mesh_body;
    is::IAnimatedMesh *mesh_head;
    is::IAnimatedMesh *mesh_weapon;
    is::IAnimatedMesh *mesh_mf;

public:
    enum Animation { RUN, WALK, ATTACK, DEATH, STAND };
    //Noeud qui mermet de manipuler le maillage
    is::IAnimatedMeshSceneNode *body;
    is::IAnimatedMeshSceneNode *head;
    is::IAnimatedMeshSceneNode *weapon;
    is::IAnimatedMeshSceneNode *mf;

    void addCharacterMeshToScene(is::ISceneManager *smgr, std::vector<video::ITexture *> tex);
    void addCharacterCollider(is::ISceneManager *smgr, scene::ITriangleSelector *selector);
    void setAnimation(Animation anim);

    void change_texture_weapon_fire(std::vector<iv::ITexture*>& textures);
    void change_texture_weapon_rest(std::vector<iv::ITexture*>& textures);

    Character(is::ISceneManager *smgr);

    Character();
};
#endif // CHARACTER_H
