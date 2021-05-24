#pragma once
#include <string>
#include "cocos2d.h"
using namespace cocos2d;

class Bomb : public cocos2d::Sprite
{
public:

    // ###################################################
    // Methods
    // ###################################################
    Bomb();
    ~Bomb();
    Bomb* create();

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


    int x;
    int y;

private:
    //virtual bool init();
    
    int customTiledPosX;
    int customTiledPosY;
    Sprite* _sprite;
    SpriteFrameCache* _spriteCacher;

};
