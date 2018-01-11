#include "enemy.h"

Enemy::Enemy(is::ISceneManager *smgr_param,
             irr::IRandomizer *random_generator_param,
             is::IAnimatedMeshSceneNode *main_character_node_param)
{
    smgr = smgr_param;
    random_generator = random_generator_param;
    mesh = smgr->getMesh("../data/tris.md2");
    waiting_position_center = {0.0f,0.0f,0.0f};
    main_character_node = main_character_node_param;
    vitesse_run = 0.9f;
    vitesse_walk = 0.5f;
    distance_min_to_trigger_chasing = 300;

}

void Enemy::addEnemyMeshToScene(){
    node = smgr->addAnimatedMeshSceneNode(mesh);
    node -> setMaterialFlag(irr::video::EMF_LIGHTING,false);
    node -> setMD2Animation(irr::scene::EMAT_STAND);
    random_walk_animator = new RandomWalkNodeAnimator(vitesse_run,vitesse_walk);
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
}
void Enemy::setID(int id){
    node ->setID(id);
}

void Enemy::move_randomely_arround_waiting_position()
{
    node ->setMD2Animation(is::EMAT_RUN);
    node->addAnimator(random_walk_animator);
}

void Enemy::create_collision_with_map(is::ITriangleSelector *world)
{
    const ic::aabbox3d<f32>& box = node->getBoundingBox();
    ic::vector3df radius = box.MaxEdge - box.getCenter();


    is::ISceneNodeAnimatorCollisionResponse *world_collision_anim_response = smgr
            ->createCollisionResponseAnimator(world,node,radius,
                                              ic::vector3df(0,-10,0));

    world_collision_anim_response->setCollisionCallback(&world_collision_response);
    node->addAnimator(world_collision_anim_response);
    //TODO drop the world_collision_anim_response when not needed anymore
}

void Enemy::handle_walking(){

    const f32 distance_to_main_character = main_character_node->getAbsolutePosition().getDistanceFrom(node->getAbsolutePosition());

    // if enemy close to main character
    if(distance_to_main_character <= distance_min_to_trigger_chasing){
        // run and chase him
        if(random_walk_animator->is_following_main_character!=true){
            random_walk_animator->is_following_main_character = true;
            node->setMD2Animation(is::EMAT_RUN);
        }

        random_walk_animator->position_main_character = main_character_node->getPosition();
    }
    else{
        //random walk
        if(random_walk_animator->is_following_main_character!=false){
            random_walk_animator->is_following_main_character = false;
            node->setMD2Animation(is::EMAT_CROUCH_WALK);
        }

    }

}
