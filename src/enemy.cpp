#include "enemy.h"

void Enemy::addEnemyMeshToScene(is::ISceneManager *smgr){
    node = smgr->addAnimatedMeshSceneNode(mesh);
    node -> setMaterialFlag(irr::video::EMF_LIGHTING,false);
    node -> setMD2Animation(irr::scene::EMAT_STAND);
}

void Enemy::setTexture(std::string path, IrrlichtDevice *device){
    if(!node){
        throw "Unable to set texture of node not defined";
    }
}



Enemy::Enemy(is::ISceneManager *smgr)
{
    mesh = smgr->getMesh("../data/tris.md2");
}
