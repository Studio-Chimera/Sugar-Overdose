#pragma once
#include <string>
#include "cocos2d.h"

using namespace cocos2d;

class PowerUP_Range
{
public:

    // ###################################################
    // Methods
    // ###################################################

    PowerUP_Range(Vec2 position, Vec2 customTiledPosition, int axis, int value);

    // ###################################################
    // Setters
    // ###################################################

    void setPosX(int newPos);
    void setPosY(int newPos);
    void setCustomTiledPosition(Vec2 customTiledPosition);
    void setAxis(int axis);
    void setValue(int value);

    // ###################################################
    // Getters
    // ###################################################

    int getAxis();
    int getValue();
    Vec2 getPosition();
    Vec2 getCustomTiledPosition();
    Sprite* getSprite();
    SpriteFrameCache* getSpritecacher();

private:

    float _posX;
    float _posY;
    int _value;
    int _axis;
    int _customTiledPosX;
    int _customTiledPosY;
    Sprite* _sprite;
    SpriteFrameCache* _spriteCacher;

};
