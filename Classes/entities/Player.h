#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include <extensions\physics-nodes\CCPhysicsSprite.h>
#include <variant>
#include "entities/Level.h"

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

    int getPosX();
    int getPosY();
    Vec2 getNextPosition(int direction);
    Vec2 getPosition();
    Sprite* getSprite();
    SpriteFrameCache* getSpritecacher();
    std::variant<EventListenerCustom*, EventListenerKeyboard*> getController();


    // ###################################################
    // Setters
    // ###################################################

    void setPosX(int newPos);
    void setPosY(int newPos);
    void setPosition(Vec2 position);
    void setSideMoveAnimation(Vector<SpriteFrame*>);
    void setTopMoveAnimation(Vector<SpriteFrame*>);
    void setBottomMoveAnimation(Vector<SpriteFrame*>);
    void setController(std::variant<EventListenerCustom*, EventListenerKeyboard*> controller);

    // ###################################################
    // Methods
    // ###################################################

    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void plantBomb();
    bool blockPlayerIfWalls(const int direction);
    bool blockPlayer(const int direction);
    
    int orthPosX;
    int orthPosY;

private:
    
    float _posX;
    float _posY;

    SpriteFrameCache* _spriteCacher;
    Sprite* _sprite;
    Animation* _sideMoveAnimation;
    Animation* _topMoveAnimation;
    Animation* _bottomMoveAnimation;
    std::variant<EventListenerCustom*, EventListenerKeyboard*> _controller;

};

#endif // __PLAYER_H__

