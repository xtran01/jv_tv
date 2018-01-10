#include "enemy.h"

Enemy::Enemy(is::ISceneManager *smgr_param,
             irr::IRandomizer *random_generator_param)
{
    smgr = smgr_param;
    random_generator = random_generator_param;
    mesh = smgr->getMesh("../data/tris.md2");
    waiting_position_center = {0.0f,0.0f,0.0f};

}

void Enemy::addEnemyMeshToScene(){
    node = smgr->addAnimatedMeshSceneNode(mesh);
    node -> setMaterialFlag(irr::video::EMF_LIGHTING,false);
    node -> setMD2Animation(irr::scene::EMAT_STAND);
}

void Enemy::setPosition(ic::vector3df vec3){
    node -> setPosition(vec3);
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

    f32 radius = 100.f;
    ic::array<ic::vector3df> points;
    for(int i = 0; i< 10; i++){
        f32 r = random_generator->frand() * radius;
        f32 teta = random_generator->frand() * M_PI * 2.0f;
        f32 test = random_generator->frand();
        ic::vector3df position = waiting_position_center;
        position.X += r*cos(teta);
        position.Z += r*sin(teta);
        points.push_back(position);
    }

   // is::ISceneNodeAnimator *anim = smgr->createFollowSplineAnimator(0.0f,
                             //  points,0.5f);
    is::ISceneNodeAnimator *anim = new RandomWalkNodeAnimator();
    node ->setMD2Animation(is::EMAT_RUN);
    node->addAnimator(anim);
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
