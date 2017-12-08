#ifndef ENEMY_H
#define ENEMY_H
#include <irrlicht.h>
#include <string>
#include <assert.h>
#include <iostream>
#include "enemycollisionhandler.h"

using namespace irr;
namespace is = irr::scene;
namespace iv = irr::video;
namespace ic = irr::core;

class Enemy
{
private:
    //Mesh associated to the enemy
    is::IAnimatedMesh * mesh;
    //Noeud qui mermet de manipuler le maillage
    is::IAnimatedMeshSceneNode *node;

    EnemyCollisionHandler world_collision_response;

    ic::vector3df waiting_position_center;

public:
    Enemy(is::ISceneManager *smgr);


    void addEnemyMeshToScene(is::ISceneManager *smgr);
    void setPosition(ic::vector3df vec3);

    /**
     * Function setTexture
     * *******************
     * Set a texture for the node of the enemy
     * require:
     * *******
     * - a path for the texture of type string
     * - the video driver of type driver
     * ensure:
     * ******
     * - texture set to the node
     * */
    void setTexture(io::path path, iv::IVideoDriver *driver);

    void create_collision_with_map(is::ITriangleSelector *world,
                                   is::ISceneManager *smgr);

    void move_randomely_arround_waiting_position(is::ISceneManager *smgr);



};

#endif // ENEMY_H
