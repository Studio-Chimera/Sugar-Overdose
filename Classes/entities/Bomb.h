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

    Bomb();
    ~Bomb();
    void spawnParticules();
    std::vector<ParticuleExplosion*> particulesExplosionList;

    // ###################################################
    // Setters
    // ###################################################

    void setCustomTiledPosition(Vec2* customTiledPosition);

    // ###################################################
    // Getters
    // ###################################################

    Sprite* getSprite();
    SpriteFrameCache* getSpritecacher();
    Vec2* getCustomTiledPosition();

private:
    
    int customTiledPosX;
    int customTiledPosY;
    Sprite* _sprite;
    SpriteFrameCache* _spriteCacher;

    void removeParticules();
};
