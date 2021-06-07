#pragma once
#include <string>
#include "cocos2d.h"
#include "ParticuleExplosion.h"
using namespace cocos2d;

class Bomb : public Sprite
{
public:

    // ###################################################
    // Methods
    // ###################################################

    Bomb(Vec2 position, Vec2 customTiledPosition, int rangeExplosionX, int rangeExplosionY);

    ~Bomb();
    void spawnParticules(int rangeX, int rangeY);
    void explosion(float currentCustomTiledXPositon, float currentCustomTiledYPositon, int rangeExplosionX, int rangeExplosionY);
    void removeOnMap(string tile, float currentCustomTiledXPositon, float currentCustomTiledYPositon);

    vector<ParticuleExplosion*> particulesExplosionList;

    // ###################################################
    // Setters
    // ###################################################

    void setCustomTiledPosition(Vec2 customTiledPosition);

    // ###################################################
    // Getters
    // ###################################################

    Sprite* getSprite();
    SpriteFrameCache* getSpritecacher();
    Vec2 getCustomTiledPosition();

private:
    
    int customTiledPosX;
    int customTiledPosY;
    Sprite* _sprite;
    SpriteFrameCache* _spriteCacher;

    void removeParticules();
};
