#include "Bomb.h"
#include "Level.h"

Bomb::Bomb(){

    _spriteCacher = SpriteFrameCache::getInstance();

    std::stringstream plistFile;
    plistFile << "sprites/bomb/bomb_.plist";
    _spriteCacher->addSpriteFramesWithFile(plistFile.str());

    std::stringstream standPng;
    standPng << "bomb1_reduced.png";
    this->_sprite = new Sprite;
    auto myfile = standPng.str();
    _sprite->initWithSpriteFrameName(myfile);
}

/*
    make appear differents particules for visual only
*/
void Bomb::spawnParticules(int rangeX, int rangeY) {


    int positionVariable = -STEP_PLAYER;

    // particules spawn on X axis
    for (int i = 1; i <= rangeX; i++) {        
        ParticuleExplosion* particuleExplosion = new ParticuleExplosion();
        particuleExplosion->getSprite()->setPosition(Vec2(getSprite()->getPosition().x + positionVariable, getSprite()->getPosition().y));
        positionVariable += STEP_PLAYER;
        Level::getInstance()->addChild(particuleExplosion->getSprite());
        particulesExplosionList.push_back(particuleExplosion);
    }

    // particules spawn on Y axis
    positionVariable = -STEP_PLAYER;
    for (int i = 1; i <= rangeY; i++) {

        ParticuleExplosion* particuleExplosion = new ParticuleExplosion();
        particuleExplosion->getSprite()->setPosition(Vec2(getSprite()->getPosition().x, getSprite()->getPosition().y + positionVariable));
        positionVariable += STEP_PLAYER;
        Level::getInstance()->addChild(particuleExplosion->getSprite());
        particulesExplosionList.push_back(particuleExplosion);
    }

    // clean map from particules
    _sprite->runAction(Sequence::create(
        DelayTime::create(TIME_PARTICULE),
        CallFunc::create(CC_CALLBACK_0(Bomb::removeParticules, this)), nullptr));
}

/*
    clean particules from bomb
*/
void Bomb::removeParticules() {
    for (auto it : particulesExplosionList) {
        it->getSprite()->removeFromParent();
    }
    particulesExplosionList.clear();
    getSprite()->removeFromParent(); // destroy bomb

}

Bomb::~Bomb(){}

Sprite* Bomb::getSprite()
{
    return _sprite;
}

SpriteFrameCache* Bomb::getSpritecacher()
{
    return _spriteCacher;
}


Vec2 Bomb::getCustomTiledPosition() {
    return Vec2(customTiledPosX, customTiledPosY);
}

void Bomb::setCustomTiledPosition(Vec2 customTiledPosition) {
    customTiledPosX = customTiledPosition.x;
    customTiledPosY = customTiledPosition.y;
}
