#ifndef ENEMY_H
#define ENEMY_H
#include "constantes.h"
#include <string>
#include <assert.h>
#include <iostream>
#include "enemycollisionhandler.h"
#include "character.h"
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
    u32 health_point = 5;
    u32 blink_frame = 0;
    enum Animation { RUN, WALK, ATTACK, DEATH, STAND };

    EnemyCollisionHandler world_collision_response;

    ic::vector3df waiting_position_center;

    RandomWalkNodeAnimator *random_walk_animator;

    is::IAnimatedMeshSceneNode *main_character_node;

    f32 vitesse_walk;
    f32 vitesse_run;

    f32 distance_min_to_trigger_chasing;

    Animation anim;


public:

    /**
     * @brief Enemy : Constructor of the Enemy
     * @param smgr_param : pointer to the scene manager
     * @param random_generator_param
     */
    Enemy();


    //Noeud qui mermet de manipuler le maillage
    is::IAnimatedMeshSceneNode *node;
    is::IAnimatedMeshSceneNode *hand;

    void addEnemyMeshToScene(is::ISceneManager* smgr,
                             is::IAnimatedMeshSceneNode *main_character_node_param,
                             irr::IRandomizer *randomizer_param);
    /**
     * @brief setPosition : Set the position of the enemy
     * @param vec3 : New position of the mesh
     */
    void setPosition(ic::vector3df vec3);
    void setRotation(ic::vector3df vec3);

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
    void setID(u32 id);

    /**
     * @brief being_hit : Set a texture / Decrease  health point / Set blink frame
     * @param texture_hit : Texture of the hitten enemy
     */
    void being_hit(video::ITexture *texture_hit);
    /**
     * @brief make_blink
     * @param texture
     */
    void make_blink(iv::ITexture *texture);
    void attack(Character *perso);
    /**
     * @brief create_collision_with_map
     * @param world
     */
    void create_collision_with_map(is::ITriangleSelector *world);
    /**
     * @brief move_randomely_arround_waiting_position
     */
    void move_randomely_arround_waiting_position();

    bool getCollision();

    /**
     * @brief follow_main_character
     * handle the walking of an enemy
     */
    void handle_walking();
    /**
     * @brief Set Animation of Enemy
     *
     */
    void setAnimation(Animation anim);




};

#endif // ENEMY_H
