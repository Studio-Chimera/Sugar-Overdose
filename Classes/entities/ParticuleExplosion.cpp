#include "ParticuleExplosion.h"
#include <entities/Level.h>

ParticuleExplosion::ParticuleExplosion() {

    _spriteCacher = SpriteFrameCache::getInstance();

    std::stringstream plistFile;
    plistFile << "sprites/bomb/bomb_.plist";
    _spriteCacher->addSpriteFramesWithFile(plistFile.str());

    std::stringstream standPng;
    standPng << "bomb3_reduced.png";
    this->_sprite = new Sprite;
    auto myfile = standPng.str();
    _sprite->initWithSpriteFrameName(myfile);
}

ParticuleExplosion::~ParticuleExplosion() {
    getSprite()->removeFromParent();
}

Sprite* ParticuleExplosion::getSprite()
{
    return _sprite;
}

void ParticuleExplosion::setCustomTiledPosition(Vec2* customTiledPosition) {
    customTiledPosX = customTiledPosition->x;
    customTiledPosY = customTiledPosition->y;
}
