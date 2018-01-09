#ifndef ENEMY_H
#define ENEMY_H
#include <irrlicht.h>
#include <string>
#include <assert.h>
#include <iostream>
#include "enemycollisionhandler.h"
#include "randomwalknodeanimator.h"


using namespace irr;
namespace is = irr::scene;
namespace iv = irr::video;
namespace ic = irr::core;
/**
 * Class to describe an enemy
 * @brief The Enemy class
 */
class Enemy
{
private:
     //pointer to the scene manager
     is::ISceneManager *smgr;
    //Mesh associated to the enemy
    is::IAnimatedMesh * mesh;
    //Noeud qui mermet de manipuler le maillage
    is::IAnimatedMeshSceneNode *node;
    //pointer to a random number generator
    irr::IRandomizer *random_generator;

    EnemyCollisionHandler world_collision_response;

    ic::vector3df waiting_position_center;


public:
    Enemy(is::ISceneManager* smgr_param,
          irr::IRandomizer *random_generator_param);


    void addEnemyMeshToScene();
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

    void create_collision_with_map(is::ITriangleSelector *world);

    void move_randomely_arround_waiting_position();



};

#endif // ENEMY_H
