#pragma once
#ifndef __LEVEL_SCENE_H__
#define __LEVEL_SCENE_H__
#include "cocos2d.h"
#include "Player.h"
#include "utils/Definitions.h"

using namespace cocos2d;

/*
 SINGLETON
*/
class Level : public Layer
{

public:

    /*
    methods
    */

    virtual bool init();
    static Scene* scene();
    bool onContactBegin(PhysicsContact& contact); // first step collision
    
    void playersCollision(PhysicsBody* physicsBodyA, PhysicsBody* physicsBodyB);
    void playerCollisionBorderMap(PhysicsBody* physicsBodyA, PhysicsBody* physicsBodyB);
    bool checkIfCollision(Vec2 nextPosition, Size sizePlayer);

    Level(Level& other) = delete;
    void operator=(const Level&) = delete;

    CREATE_FUNC(Level); // implement the "static create()" method manually

    /*
        getters
    */

    static Level* getInstance();
    
    //int getTileGid(Vec2 position);
    Vector<TMXLayer*> getLayersLevel();
    //Vec2 Level::getTileCoordForPosition(Vec2 position);
    //Sprite* Level::getTileCoordForPosition(Vec2 position, Size size);
    
    /*
        setters
    */
    

protected:
    Level(){}
    ~Level(){}
    
    static Level* levelInstance;

private:

    //Player* player1;
    //Player* player2;
    //Player* player3;
    //Player* player4;
    
    Vector<Rect*>* obstaclesWalls;
    Vector<Rect*>* obstaclesBorders;

    TMXTiledMap* tileMap;
    TMXLayer* tilesBackground;
    TMXLayer* tilesWalls;
    TMXLayer* tilesBorders;
    
    PhysicsWorld* _sceneWorld;

    void createPhysicalWorld(PhysicsWorld* world) { _sceneWorld = world; };

};


#endif // __LEVEL_SCENE_H__
