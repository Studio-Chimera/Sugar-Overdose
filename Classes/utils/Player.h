#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include <extensions\physics-nodes\CCPhysicsSprite.h>
#include <variant>

using namespace cocos2d;

class Player
{
public:

    // ###################################################
    // Declarations
    // ###################################################

    Player();
    ~Player();

    // ###################################################
    // Getters
    // ###################################################

    Sprite* getSprite();
    SpriteFrameCache* getSpritecacher();
    int getPosX();
    int getPosY();
    Vec2 getPosition();
    std::variant<EventListenerCustom*, EventListenerKeyboard*> getController();

    // ###################################################
    // Setters
    // ###################################################

    void setPosX(int newPos);
    void setPosY(int newPos);
    void setPosition(Vec2* position);
    void setSideMoveAnimation(Vector<SpriteFrame*>);
    void setTopMoveAnimation(Vector<SpriteFrame*>);
    void setBottomMoveAnimation(Vector<SpriteFrame*>);
    void setController(std::variant<EventListenerCustom*, EventListenerKeyboard*> controller);

    // ###################################################
    // Methods
    // ###################################################

    void moveLeft();
    void moveRight();
    void moveTop();
    void moveBottom();
    void plantBomb();
    void actualizePosition();

private:
    SpriteFrameCache* _spriteCacher;
    Sprite* _sprite;
    int _posX;
    int _posY;
    Animation* _sideMoveAnimation;
    Animation* _topMoveAnimation;
    Animation* _bottomMoveAnimation;
    std::variant<EventListenerCustom*, EventListenerKeyboard*> _controller;

};

#endif // __PLAYER_H__

