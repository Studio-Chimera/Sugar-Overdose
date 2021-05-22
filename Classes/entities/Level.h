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
    bool checkIfCollision(Vec2 nextPosition, Size sizePlayer);
    bool NEWcheckIfCollision(Vec2 nextPosition);

    Level(Level& other) = delete;
    void operator=(const Level&) = delete;

    CREATE_FUNC(Level); // implement the "static create()" method manually

    /*
        getters
    */
    static Level* getInstance();
    
    Vector<TMXLayer*> getLayersLevel();

protected:
    Level(){}
    ~Level(){}
    
    static Level* levelInstance;

private:
    
    Vector<Rect*>* obstaclesWalls;
    Vector<Rect*>* obstaclesBorders;
    vector<vector<string>>* map;

    TMXTiledMap* tileMap;
    TMXLayer* tilesBackground;
    TMXLayer* tilesWalls;
    TMXLayer* tilesBorders;
};


#endif // __LEVEL_SCENE_H__
