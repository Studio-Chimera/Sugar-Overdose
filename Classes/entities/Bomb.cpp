#include "Bomb.h"
#include "Level.h"
#include <helpers/PlayerHelper.h>

Bomb::Bomb(Vec2 position, Vec2 customTiledPosition, int rangeExplosionX, int rangeExplosionY){

    // Setup sprite
    _spriteCacher = SpriteFrameCache::getInstance();

    std::stringstream plistFile;
    plistFile << "sprites/bomb/bomb_.plist";
    _spriteCacher->addSpriteFramesWithFile(plistFile.str());

    std::stringstream standPng;
    standPng << "bomb1_reduced.png";
    this->_sprite = new Sprite;
    auto myfile = standPng.str();
    _sprite->initWithSpriteFrameName(myfile);

    // Place sprite
    Level::getInstance()->addChild(getSprite());
    getSprite()->setPosition(position);
    setCustomTiledPosition(customTiledPosition);

    // Trigger the explosion after TIME_EXPLOSION delay
    _sprite->runAction(Sequence::create(
        DelayTime::create(TIME_EXPLOSION),
        CallFunc::create(CC_CALLBACK_0(Bomb::explosion, this, customTiledPosition.x, customTiledPosition.y, rangeExplosionX, rangeExplosionY)), nullptr));
}

Bomb::~Bomb(){}

void Bomb::explosion(float customTiledXMap, float customTiledYMap, int rangeExplosionX, int rangeExplosionY) {

    spawnParticules(rangeExplosionX, rangeExplosionY);

    auto mapLevel = Level::getInstance()->customTiledMap;
    const int widthMap = Level::getInstance()->tileMap->getMapSize().width;
    const int heightMap = Level::getInstance()->tileMap->getMapSize().height;

    removeOnMap(mapLevel->at(customTiledXMap).at(customTiledYMap), customTiledXMap, customTiledYMap);

    // fill the X axis with custom tiled map
    int x = -1;
    for (int i = 1; i <= rangeExplosionX; i++) {
        if (customTiledXMap + x > 0) { // explosion is at left of the bomb
            removeOnMap(mapLevel->at(customTiledXMap + x).at(customTiledYMap), customTiledXMap + x, customTiledYMap);
        }
        
        x = -x;
        if (customTiledXMap + x < widthMap) { // explosion is at right of the bomb
            removeOnMap(mapLevel->at(customTiledXMap + x).at(customTiledYMap), customTiledXMap + x, customTiledYMap);
        }
        
        if (x > 0) {
            x = -x;
            x--;
        }
    }

    // fill the T axis with custom tiled map
    int y = -1;
    for (int i = 1; i <= rangeExplosionY; i++) {
        
        if (customTiledYMap + y > 0) { // explosion is at top of the bomb
            removeOnMap(mapLevel->at(customTiledXMap).at(customTiledYMap + y), customTiledXMap, customTiledYMap + y);
        }
        
        y = -y;
        if (customTiledYMap + y < heightMap) { // explosion is at bottom of the bomb
            removeOnMap(mapLevel->at(customTiledXMap).at(customTiledYMap + y), customTiledXMap, customTiledYMap + y);
        }
        
        if (y > 0) {
            y = -y;
            y--;
        }
    }
}

/*
    make appear differents particules for visual only
*/
void Bomb::spawnParticules(int rangeX, int rangeY) {


    int positionVariable = -STEP_PLAYER;

    // particules spawn on X axis
    for (int i = 0; i < rangeX; i++) {
        ParticuleExplosion* particuleExplosion = new ParticuleExplosion();
        particuleExplosion->getSprite()->setPosition(Vec2(getSprite()->getPosition().x + positionVariable, getSprite()->getPosition().y));
        positionVariable += STEP_PLAYER;
        Level::getInstance()->addChild(particuleExplosion->getSprite());
        particulesExplosionList.push_back(particuleExplosion);
    }

    // particules spawn on Y axis
    positionVariable = -STEP_PLAYER;
    for (int i = 0; i < rangeY; i++) {

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
void Bomb::removeOnMap(string tile, float customTiledXMap, float customTiledYMap) {

    auto mapLevel = Level::getInstance()->customTiledMap;

    if (tile == "Player_1") {
        mapLevel->at(customTiledXMap).at(customTiledYMap) = "Empty";
        PlayerHelper::getInstance()->getPlayers().front()->~Player();
    }

    else if (tile == "Player_2") {
        mapLevel->at(customTiledXMap).at(customTiledYMap) = "Empty";
        PlayerHelper::getInstance()->getPlayers().back()->~Player();
    }

    else if (tile == "Wall") {
        Level::getInstance()->tilesWalls->removeTileAt(Vec2(customTiledXMap, customTiledYMap));
        mapLevel->at(customTiledXMap).at(customTiledYMap) = "Empty";
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
