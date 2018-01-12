#include "enemy.h"

Enemy::Enemy()
{
    vitesse_run = RUN_VITESSE_ENEMY;
    vitesse_walk = WALK_VITESSE_ENEMY;
    distance_min_to_trigger_chasing = DISTANCE_MIN_TO_CHASE_MAIN_CHARACTER;
}

/**
 * Called to add an enemy mesh to the scene
 * @brief Enemy::addEnemyMeshToScene
 * @param smgr => scene manager related to the game
 * @param main_character_node_param => node related to the main character of the game
 * @param randomizer_param => randomizer to create random numbers
 */
void Enemy::addEnemyMeshToScene(is::ISceneManager* smgr,
                                is::IAnimatedMeshSceneNode *main_character_node_param,
                                irr::IRandomizer *randomizer_param){

    is::IAnimatedMesh *mesh = smgr->getMesh("../data/Baron/BaronBody.md2");
    is::IAnimatedMesh *mesh_hand = smgr->getMesh("../data/Baron/BaronHands.md2");

    main_character_node = main_character_node_param;
    node = smgr->addAnimatedMeshSceneNode(mesh);
    hand = smgr->addAnimatedMeshSceneNode(mesh_hand,node,-1,core::vector3df(0,0,0),core::vector3df(0,0,0));
    mesh->drop();
    node -> setMaterialFlag(irr::video::EMF_LIGHTING,false);
    (this)->setAnimation((this)->STAND);
    is::ITriangleSelector *selector = smgr->createTriangleSelector(node);
    node->setTriangleSelector(selector);
    selector->drop();
    // adding a random walk to the enemy
    random_walk_animator = new RandomWalkNodeAnimator(vitesse_run,vitesse_walk,randomizer_param);
}

void Enemy::setPosition(ic::vector3df vec3){
    node -> setPosition(vec3);
}

void Enemy::setRotation(ic::vector3df vec3){
    node -> setRotation(vec3);
}

void Enemy::setTexture(iv::ITexture *texture){
    assert(node != NULL);
    node->setMaterialTexture(0, texture);
    hand->setMaterialTexture(0,texture);
}

void Enemy::setID(u32 id){
    node ->setID(id);
}

void Enemy::being_hit(iv::ITexture* texture_hit){
    if (health_point > 0){
        health_point--;
        blink_frame = 15;
        node->setMaterialTexture(0, texture_hit);
    }
    if (health_point == 0){
        node->setVisible(false);
    }
}

/**
 * Add the random walk animator to the node of the enemy
 * @brief Enemy::move_randomely_arround_waiting_position
 */
void Enemy::move_randomely_arround_waiting_position()
{
    (this)->setAnimation((this)->RUN);
    node->addAnimator(random_walk_animator);
}

void Enemy::make_blink(video::ITexture *texture)
{
    if(blink_frame>0){
        blink_frame--;
    }
    else{
        node->setMaterialTexture(0, texture);
    }
}

void Enemy::attack(Character *perso)
{
    if(health_point > 0){
        ic::vector3df pos_player = perso->body->getPosition();

        if (pos_player.getDistanceFrom(node->getPosition())< 60.0){
            perso->take_damage();
            if((this)->anim != (this)->ATTACK)
                (this)->setAnimation((this)->ATTACK);


        }

    }
}

/**
 * Create an animator that will handle the collision with the worlkdaa
 * @brief Enemy::create_collision_with_map
 * @param world
 */
void Enemy::create_collision_with_map(is::ITriangleSelector *world)
{
    const ic::aabbox3d<f32>& box = node->getBoundingBox();
    ic::vector3df radius = box.MaxEdge - box.getCenter();


    is::ISceneNodeAnimatorCollisionResponse *world_collision_anim_response = node->getSceneManager()
            ->createCollisionResponseAnimator(world,node,radius+10,
                                              ic::vector3df(0,-10,0),ic::vector3df(0,-52,0));
    //We have customize the collision response in the class  EnemyCollisionHandler
    world_collision_anim_response->setCollisionCallback(&world_collision_response);
    node->addAnimator(world_collision_anim_response);
}

void Enemy::handle_walking(){

    const f32 distance_to_main_character = main_character_node->getAbsolutePosition().getDistanceFrom(node->getAbsolutePosition());

    // if enemy close to main character
    if(distance_to_main_character <= distance_min_to_trigger_chasing){
        // run and chase him
        if(random_walk_animator->is_following_main_character!=true){
            random_walk_animator->is_following_main_character = true;
            (this)->setAnimation((this)->RUN);
        }

        random_walk_animator->position_main_character = main_character_node->getPosition();
    }
    else{
        //random walk
        if(random_walk_animator->is_following_main_character!=false){
            random_walk_animator->is_following_main_character = false;
            (this)->setAnimation((this)->WALK);
        }

    }

}

void Enemy::setAnimation(Animation anim)
{
    switch(anim)
    {
    case RUN:
        node->setFrameLoop(5,31);
        node->setAnimationSpeed(50.0);
        hand->setFrameLoop(5,31);
        hand->setAnimationSpeed(50.0);
        (this)->anim = (this)->RUN;
        break;
    case WALK:
        node->setFrameLoop(5,31);
        node->setAnimationSpeed(20.0);
        hand->setFrameLoop(5,31);
        hand->setAnimationSpeed(20.0);
        (this)->anim = (this)->WALK;
        break;
    case ATTACK:
        node->setFrameLoop(50,78);
        node->setAnimationSpeed(50.0);
        hand->setFrameLoop(50,78);
        hand->setAnimationSpeed(50.0);
        (this)->anim = (this)->ATTACK;
        break;
    case DEATH:
        node->setFrameLoop(0,0);
        node->setAnimationSpeed(40.0);
        hand->setFrameLoop(0,0);
        hand->setAnimationSpeed(40.0);
        (this)->anim = (this)->DEATH;
        break;
    case STAND:
        node->setFrameLoop(0,0);
        hand->setFrameLoop(0,0);
        (this)->anim = (this)->STAND;
        break;
    }
}


