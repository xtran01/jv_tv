#include "enemy.h"

void Enemy::addEnemyMeshToScene(is::ISceneManager *smgr){
    node = smgr->addAnimatedMeshSceneNode(mesh);
    node -> setMaterialFlag(irr::video::EMF_LIGHTING,false);
    node -> setMD2Animation(irr::scene::EMAT_STAND);
}

void Enemy::setPosition(ic::vector3df vec3){
    node -> setPosition(vec3);
}

void Enemy::setID(s32 id){
    node -> setID(id);
}

void Enemy::setTexture(iv::ITexture *tex){
    assert(node != NULL);
    node->setMaterialTexture(0, tex);
}


Enemy::Enemy(is::ISceneManager *smgr)
{
    mesh = smgr->getMesh("../data/tris.md2");
}
