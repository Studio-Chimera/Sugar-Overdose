#pragma once
#ifndef __LEVEL_SCENE_H__
#define __LEVEL_SCENE_H__

#include "cocos2d.h"
#include "Player.h"
#include "utils/Definitions.h"
#include "PowerUP_Range.h"

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
    static Scene* scene(string level);
    void countdown();
    void displayCountDown(int time, Sprite* counter);
    
    vector<vector<string>>* customTiledMap;
    Sprite* counter;

    bool checkIfCollisions(Vec2 nextPosition, int direction, Player* player);
    void cleanOldPosition(Vec2 nextTiledPosition, int direction);
    void start(EventListenerKeyboard* player1Controller, EventListenerKeyboard* player2Controller);

    Level(Level& other) = delete;
    void operator=(const Level&) = delete;

    CREATE_FUNC(Level); // implement the "static create()" method manually

    // ###################################################
    // Getters
    // ###################################################
    
    string getLevelName();
    static Level* getInstance();
    TMXLayer* tilesWalls;
    TMXTiledMap* tileMap;
    TMXLayer* tilesBackground;
    TMXLayer* tilesBorders;

    // ###################################################
    // Setters
    // ###################################################

    static void setLevelName(string level);
    void setNewPositionPlayerOnCustomTiledMap(Vec2 nextTiledPosition, int direction, int playerNumber);

protected:


private:

    Level() {}
    ~Level() {}
    void fillCustomTiledMap();

    static string _levelName;
    float mapWidth;
    float mapHeight;
    Vector<Rect*>* obstaclesWalls;
    Vector<Rect*>* obstaclesBorders;
    vector<PowerUP_Range*> powerRangeVector;
    vector<Vec2> customTiledPositionOfItems;
    static Level* levelInstance;
    
};

#endif // __LEVEL_SCENE_H__
