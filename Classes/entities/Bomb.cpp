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
void Bomb::spawnParticules() {

    // particules positions
    vector<Vec2> allPositions;
    allPositions.push_back(getSprite()->getPosition());
    allPositions.push_back(Vec2(getSprite()->getPosition().x + 167, getSprite()->getPosition().y)); // Sprite on right
    allPositions.push_back(Vec2(getSprite()->getPosition().x - 167, getSprite()->getPosition().y)); // Sprite on left
    allPositions.push_back(Vec2(getSprite()->getPosition().x, getSprite()->getPosition().y - 167)); // Sprite on top
    allPositions.push_back(Vec2(getSprite()->getPosition().x, getSprite()->getPosition().y + 167)); // Sprite on bottom

    // particules creations
    for (int i = 0; i <= 4; i++) {
        particulesExplosionList.push_back(new ParticuleExplosion);
    }

    // particules spawns
    for (auto it : particulesExplosionList) {
        for (auto itPosition : allPositions) {
            it->getSprite()->setPosition(itPosition);
            Level::getInstance()->addChild(it->getSprite());
            allPositions.erase(allPositions.begin());
            break;
        }
    }

    // clean map from particules
    _sprite->runAction(Sequence::create(
        DelayTime::create(TIME_EXPLOSION),
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


Vec2* Bomb::getCustomTiledPosition() {
    return new Vec2(customTiledPosX, customTiledPosY);
}

void Bomb::setCustomTiledPosition(Vec2* customTiledPosition) {
    customTiledPosX = customTiledPosition->x;
    customTiledPosY = customTiledPosition->y;
}
