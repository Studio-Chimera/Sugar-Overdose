#pragma once
#ifndef __LEVEL_SCENE_H__
#define __LEVEL_SCENE_H__

#include "cocos2d.h"
#include "Player.h"
#include "utils/Definitions.h"
//#include "PowerUp.h"

using namespace cocos2d;

/*
 SINGLETON
*/
class Level : public Layer
{

public:

    // ###################################################
    // Methods
    // ###################################################

    virtual bool init();
    static Scene* scene();
    vector<vector<string>>* customTiledMap;

    bool checkIfCollisions(Vec2 nextPosition, int direction, Player* player);
    void cleanOldPosition(Vec2 nextTiledPosition, int direction);

    Level(Level& other) = delete;
    void operator=(const Level&) = delete;

    CREATE_FUNC(Level); // implement the "static create()" method manually

    // ###################################################
    // Getters
    // ###################################################
    
    static Level* getInstance();
    TMXLayer* tilesWalls;
    TMXTiledMap* tileMap;
    TMXLayer* tilesBackground;
    TMXLayer* tilesBorders;

    // ###################################################
    // Setters
    // ###################################################

    void setNewPositionPlayerOnCustomTiledMap(Vec2 nextTiledPosition, int direction, int playerNumber);

protected:
    Level(){}
    ~Level(){}
    
    static Level* levelInstance;

private:
    
    float mapWidth;
    float mapHeight;
    Vector<Rect*>* obstaclesWalls;
    Vector<Rect*>* obstaclesBorders;
    //Vector<PowerUp*> powerRangeVector;
    Vector<pair<string, Value>>* spawnsVector;

    void fillCustomTiledMap();
    
};

#endif // __LEVEL_SCENE_H__
