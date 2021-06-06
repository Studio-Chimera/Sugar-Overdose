#pragma once

#include "cocos2d.h"
#include <extensions\physics-nodes\CCPhysicsSprite.h>
#include <string>
#include <variant>
#include "Bomb.h"

using namespace cocos2d;
using namespace std;

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

    int getPlayerNumber();
    int getPosX();
    int getPosY();
    int getRangeExplosionY();
    int getRangeExplosionX();
    Vec2 getCustomTiledPosition();
    Vec2 getNextPositionOnCustomeTiledMap(int direction);
    Vec2 getPosition();
    Sprite* getSprite();
    SpriteFrameCache* getSpritecacher();
    std::variant<EventListenerCustom*, EventListenerKeyboard*> getController();

    // ###################################################
    // Setters
    // ###################################################

    void setPlayerNumber(int playerNumber);
    void setPosX(int newPos);
    void setPosY(int newPos);
    void incrementRangeExplosionY(int rangeExplosion);
    void incrementRangeExplosionX(int rangeExplosion);
    void setPosition(Vec2 position);
    void setCustomTiledPosition(Vec2 customTiledPosition);
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

private:
    
    float _posX;
    float _posY;
    int customTiledPosX;
    int customTiledPosY;
    int _rangeExplosionX = 1;
    int _rangeExplosionY = 1;
    int playerNumber;
    
    SpriteFrameCache* _spriteCacher;
    Sprite* _sprite;
    Animation* _sideMoveAnimation;
    Animation* _topMoveAnimation;
    Animation* _bottomMoveAnimation;
    std::variant<EventListenerCustom*, EventListenerKeyboard*> _controller;

};