#ifndef CHARACTER_H
#define CHARACTER_H
#include <irrlicht.h>
#include <string>
#include <assert.h>
#include <iostream>

using namespace irr;
namespace is = irr::scene;
namespace iv = irr::video;
namespace ic = irr::core;

class Character
{
private:
    //Mesh associated to the enemy
    is::IAnimatedMesh *mesh;
public:
    //Noeud qui mermet de manipuler le maillage
    is::IAnimatedMeshSceneNode *node;
    void addCharacterMeshToScene(is::ISceneManager *smgr, iv::ITexture *tex);
    void addCharacterCollider(is::ISceneManager *smgr, scene::ITriangleSelector *selector);


    Character(is::ISceneManager *smgr);
};
#endif // CHARACTER_H
