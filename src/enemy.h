#ifndef ENEMY_H
#define ENEMY_H
#include <irrlicht.h>
#include <string>

using namespace irr;
namespace is = irr::scene;
class Enemy
{
private:
    //Mesh associated to the enemy
    is::IAnimatedMesh * mesh;
    //Noeud qui mermet de manipuler le maillage
    is::IAnimatedMeshSceneNode *node;

public:
    void addEnemyMeshToScene(is::ISceneManager *smgr);
    void setTexture(std::string path, IrrlichtDevice *device);
    Enemy(is::ISceneManager *smgr);
};

#endif // ENEMY_H
