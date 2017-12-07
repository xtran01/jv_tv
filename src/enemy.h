#ifndef ENEMY_H
#define ENEMY_H
#include <irrlicht.h>
#include <string>
#include <assert.h>
#include <iostream>


using namespace irr;
namespace is = irr::scene;
namespace iv = irr::video;

class Enemy
{
private:
    //Mesh associated to the enemy
    is::IAnimatedMesh * mesh;
    //Noeud qui mermet de manipuler le maillage
    is::IAnimatedMeshSceneNode *node;

public:
    void addEnemyMeshToScene(is::ISceneManager *smgr);
    void setTexture(io::path path, iv::IVideoDriver *driver);
    Enemy(is::ISceneManager *smgr);
};

#endif // ENEMY_H
