#include "enemy.h"

void Enemy::addEnemyMeshToScene(is::ISceneManager *smgr){
    node = smgr->addAnimatedMeshSceneNode(mesh);
    node -> setMaterialFlag(irr::video::EMF_LIGHTING,false);
    node -> setMD2Animation(irr::scene::EMAT_STAND);
}

void Enemy::setPosition(ic::vector3df vec3){
    node -> setPosition(vec3);
}



void Enemy::setTexture(io::path path, iv::IVideoDriver *driver){
    assert(node != NULL);
    node->setMaterialTexture(0, driver->getTexture(path));
}


Enemy::Enemy(is::ISceneManager *smgr)
{
    mesh = smgr->getMesh("../data/tris.md2");
}
