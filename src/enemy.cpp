#include "enemy.h"

void Enemy::addEnemyMeshToScene(is::ISceneManager *smgr){
    node = smgr->addAnimatedMeshSceneNode(mesh);
    node -> setMaterialFlag(irr::video::EMF_LIGHTING,false);
    node -> setMD2Animation(irr::scene::EMAT_STAND);
}

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
void Enemy::setTexture(io::path path, iv::IVideoDriver *driver){
    assert(node != NULL);
    node->setMaterialTexture(0, driver->getTexture(path));
}



Enemy::Enemy(is::ISceneManager *smgr)
{
    mesh = smgr->getMesh("../data/tris.md2");
}
