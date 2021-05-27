#pragma once
#include <string>
#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

class ParticuleExplosion : public Sprite
{
public:

    // ###################################################
    // Methods
    // ###################################################

    ParticuleExplosion();
    ~ParticuleExplosion();
        
    // ###################################################
    // Setters
    // ###################################################

    void setCustomTiledPosition(Vec2 customTiledPosition);

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

};