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

    void setBPosition(Vec2 position);

    // ###################################################
    // Getters
    // ###################################################

    Sprite* getSprite();
    SpriteFrameCache* getSpritecacher();

    int x;
    int y;

private:
    //virtual bool init();
    
    Sprite* _sprite;
    SpriteFrameCache* _spriteCacher;

};
