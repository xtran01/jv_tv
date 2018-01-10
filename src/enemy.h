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

    /**
      * @brief smgr : pointer to the scene manager
      */
     is::ISceneManager *smgr;
     /**
     * @brief mesh : Mesh associated to the enemy
     */
    is::IAnimatedMesh * mesh;
    /**
     * @brief random_generator : pointer to a random number generator
     */
    irr::IRandomizer *random_generator;

    EnemyCollisionHandler world_collision_response;

    ic::vector3df waiting_position_center;

    RandomWalkNodeAnimator *random_walk_animator;

    is::IAnimatedMeshSceneNode *main_character_node;


public:
    /**
     * @brief Enemy : Constructor of the Enemy
     * @param smgr_param : pointer to the scene manager
     * @param random_generator_param
     */
    Enemy(is::ISceneManager* smgr_param,
          irr::IRandomizer *random_generator_param,
          is::IAnimatedMeshSceneNode *main_character_node_param);

    //Noeud qui mermet de manipuler le maillage
    is::IAnimatedMeshSceneNode *node;
    void addEnemyMeshToScene();
    void setPosition(ic::vector3df vec3);

    /**
     * @brief Set a texture for the node of the enemy
     * require
     * @param texture : Texture
     */
    void setTexture(iv::ITexture *texture);
    /**
     * @brief setID : Set the node ID of the Enemy
     * @param id : An ID number
     */
    void setID(int id);
    /**
     * @brief create_collision_with_map
     * @param world
     */
    void create_collision_with_map(is::ITriangleSelector *world);
    /**
     * @brief move_randomely_arround_waiting_position
     */
    void move_randomely_arround_waiting_position();

    /**
     * @brief follow_main_character
     * Follow the main character
     */
    void follow_main_character();



};

#endif // ENEMY_H
