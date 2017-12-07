#ifndef ENEMY_H
#define ENEMY_H
#include <irrlicht.h>

using namespace irr;
namespace is = irr::scene;
class Enemy
{
private:
    //Mesh associated to the enemy
    is::IAnimatedMesh * mesh;
public:
    void addEnemyMeshToScene(is::ISceneManager *smgr);
    Enemy();
};

#endif // ENEMY_H
