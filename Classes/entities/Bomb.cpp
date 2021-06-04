#include "Bomb.h"
#include "Level.h"
#include <helpers/PlayerHelper.h>

Bomb::Bomb(Vec2 position, Vec2 customTiledPosition, int rangeExplosionX, int rangeExplosionY){

    _spriteCacher = SpriteFrameCache::getInstance();

    std::stringstream plistFile;
    plistFile << "sprites/bomb/bomb_.plist";
    _spriteCacher->addSpriteFramesWithFile(plistFile.str());

    std::stringstream standPng;
    standPng << "bomb1_reduced.png";
    this->_sprite = new Sprite;
    auto myfile = standPng.str();
    _sprite->initWithSpriteFrameName(myfile);

    Level::getInstance()->addChild(getSprite());

    getSprite()->setPosition(position);
    setCustomTiledPosition(customTiledPosition);

    // Trigger the explosion after TIME_EXPLOSION delay
    _sprite->runAction(Sequence::create(
        DelayTime::create(TIME_EXPLOSION),
        CallFunc::create(CC_CALLBACK_0(Bomb::explosion, this, customTiledPosition.x, customTiledPosition.y, rangeExplosionX, rangeExplosionY)), nullptr));
}

Bomb::~Bomb(){}

void Bomb::explosion(float currentCustomTiledXPositon, float currentCustomTiledYPositon, int rangeExplosionX, int rangeExplosionY) {

    spawnParticules(rangeExplosionX, rangeExplosionY);

    auto mapLevel = Level::getInstance()->customTiledMap;

    string currentTile = mapLevel->at(currentCustomTiledXPositon).at(currentCustomTiledYPositon);
    string tileRight = mapLevel->at(currentCustomTiledXPositon + 1).at(currentCustomTiledYPositon);
    string tileLeft = mapLevel->at(currentCustomTiledXPositon - 1).at(currentCustomTiledYPositon);
    string tileBottom = mapLevel->at(currentCustomTiledXPositon).at(currentCustomTiledYPositon + 1);
    string tileTop = mapLevel->at(currentCustomTiledXPositon).at(currentCustomTiledYPositon - 1);

    removeOnMap(currentTile, currentCustomTiledXPositon, currentCustomTiledYPositon);
    removeOnMap(tileRight, currentCustomTiledXPositon + 1, currentCustomTiledYPositon);
    removeOnMap(tileLeft, currentCustomTiledXPositon - 1, currentCustomTiledYPositon);
    removeOnMap(tileBottom, currentCustomTiledXPositon, currentCustomTiledYPositon + 1);
    removeOnMap(tileTop, currentCustomTiledXPositon, currentCustomTiledYPositon - 1);
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

/*
    Update custom tiled map to set "Empty" where elements are destroyed
*/
void Bomb::removeOnMap(string tile, float currentCustomTiledXPositon, float currentCustomTiledYPositon) {

    auto mapLevel = Level::getInstance()->customTiledMap;

    if (tile == "Player_1") {
        mapLevel->at(currentCustomTiledXPositon).at(currentCustomTiledYPositon) = "Empty";
        PlayerHelper::getInstance()->getPlayers().front()->~Player();
    }

    else if (tile == "Player_2") {
        mapLevel->at(currentCustomTiledXPositon).at(currentCustomTiledYPositon) = "Empty";
        PlayerHelper::getInstance()->getPlayers().back()->~Player();
    }

    else if (tile == "Wall") {
        Level::getInstance()->tilesWalls->removeTileAt(Vec2(currentCustomTiledXPositon, currentCustomTiledYPositon));
        mapLevel->at(currentCustomTiledXPositon).at(currentCustomTiledYPositon) = "Empty";
    }
}

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
