#include "enemy.h"

void Enemy::addEnemyMeshToScene(is::ISceneManager *smgr){
    node = smgr->addAnimatedMeshSceneNode(mesh);
    node -> setMaterialFlag(irr::video::EMF_LIGHTING,false);
    node -> setMD2Animation(irr::scene::EMAT_STAND);
}


void Enemy::setTexture(io::path path, iv::IVideoDriver *driver){
    assert(node != NULL);
    node->setMaterialTexture(0, driver->getTexture(path));
}


Enemy::Enemy(is::ISceneManager *smgr)
{
    mesh = smgr->getMesh("../data/tris.md2");
    waiting_position_center = {0.0f,0.0f,0.0f};
}

void Enemy::move_randomely_arround_waiting_position(is::ISceneManager *smgr)
{
    is::ISceneNodeAnimator *anim =  smgr->
            createFlyCircleAnimator(waiting_position_center,
                                    200.f);
    ic::vector3df position = node->getPosition();
    bool collisionOccured =
    position += ic::vector3df(0.5f,0.0,0.0);
    node->setPosition(position);
}

void Enemy::create_collision_with_map(is::ITriangleSelector *world,
                                      is::ISceneManager *smgr)
{
    const ic::aabbox3d<f32>& box = node->getBoundingBox();
    ic::vector3df radius = box.MaxEdge - box.getCenter();
    is::ISceneNodeAnimator *anim = smgr
            ->createCollisionResponseAnimator(world,node,radius,
                                             ic::vector3df(0,-10,0));
    worldCollisionResponse = anim;
    //node->addAnimator(anim);
}
