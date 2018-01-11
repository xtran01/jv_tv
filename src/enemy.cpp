#include "enemy.h"
#include <irrlicht.h>

Enemy::Enemy()
{
    waiting_position_center = {0.0f,0.0f,0.0f};
    vitesse_run = 0.9f;
    vitesse_walk = 0.5f;
    distance_min_to_trigger_chasing = 300;

}


void Enemy::addEnemyMeshToScene(is::ISceneManager* smgr,
                                is::IAnimatedMeshSceneNode *main_character_node_param){

    is::IAnimatedMesh *mesh = smgr->getMesh("../data/tris.md2");

    main_character_node = main_character_node_param;
    node = smgr->addAnimatedMeshSceneNode(mesh);
    mesh->drop();
    node -> setMaterialFlag(irr::video::EMF_LIGHTING,false);
    node -> setMD2Animation(irr::scene::EMAT_STAND);
    is::ITriangleSelector *selector = smgr->createTriangleSelector(node);
    node->setTriangleSelector(selector);
    selector->drop();
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

void Enemy::being_hit(iv::ITexture* texture_hit){
    if (health_point > 0){
        std::cout<<health_point<<std::endl;
        health_point--;
        blink_frame = 15;
        node->setMaterialTexture(0, texture_hit);
    }
    if (health_point == 0){
        node->setVisible(false);
       /** A MODIFIER ! FAIRE MOURIR LES ENEMIS PLUTOT **/
        //node->setMD2Animation(is::EMAT_DEATH_FALLBACKSLOW);
    }
}


void Enemy::move_randomely_arround_waiting_position()
{
    node ->setMD2Animation(is::EMAT_RUN);
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
        node ->setMD2Animation(is::EMAT_ATTACK);

    }
//    else
//        node ->setMD2Animation(is::EMAT_STAND);

    }
}

void Enemy::create_collision_with_map(is::ITriangleSelector *world)
{
    const ic::aabbox3d<f32>& box = node->getBoundingBox();
    ic::vector3df radius = box.MaxEdge - box.getCenter();


    is::ISceneNodeAnimatorCollisionResponse *world_collision_anim_response = node->getSceneManager()
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


/*
bool Enemy::getCollision()
{
        ic::list< scene::ISceneNodeAnimator*>::ConstIterator begin = mesh->getAnimators().begin();
        ic::list< scene::ISceneNodeAnimator*>::ConstIterator end   = mesh->getAnimators().end();

        for(; begin != end; ++begin)
        {
                 scene::ISceneNodeAnimator* anm = *begin;

                if(anm->getType() == ESNAT_COLLISION_RESPONSE)
                {
                        if( ((scene::ISceneNodeAnimatorCollisionResponse*)anm)->collisionOccurred())
                                return true;
                }
        }

        return false;
}*/

