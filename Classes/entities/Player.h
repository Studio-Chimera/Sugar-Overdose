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

    Sprite* getSprite();
    SpriteFrameCache* getSpritecacher();
    int getPosX();
    int getPosY();
    Vec2 getPosition();
    std::variant<EventListenerCustom*, EventListenerKeyboard*> getController();
    //Level* getLevel();
    Vec2 getTileCoordForPosition(Vec2 position);

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
    void setPlayerPosition();
    //void setLevel(Level* level);

    // ###################################################
    // Methods
    // ###################################################

    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void plantBomb();
    void stopAnimation(cocos2d::RepeatForever* ani);

private:
    SpriteFrameCache* _spriteCacher;
    Sprite* _sprite;

    int _posX;
    int _posY;
    //Level* _level;
    Animation* _sideMoveAnimation;
    Animation* _topMoveAnimation;
    Animation* _bottomMoveAnimation;
    std::variant<EventListenerCustom*, EventListenerKeyboard*> _controller;

};

#endif // __PLAYER_H__
