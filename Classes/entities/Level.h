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
    bool onContactPreSolve(PhysicsContact& contact); // second step collision
    
    Level(Level& other) = delete;
    void operator=(const Level&) = delete;

    // implement the "static create()" method manually
    CREATE_FUNC(Level);

    /*
    getters
    */

    static Level* getInstance();
    
    int getTileGid(Vec2 position);
    Vector<TMXLayer*> getLayersLevel();
    Vec2 Level::getTileCoordForPosition(Vec2 position);

    /*
    setters
    */
    

protected:
    Level(){}
    ~Level(){}
    
    static Level* levelInstance;

private:

    //static std::mutex mutex;

    TMXTiledMap* _tileMap;
    TMXLayer* _background;
    TMXLayer* _walls;
    PhysicsWorld* _sceneWorld;

    void createPhysicalWorld(PhysicsWorld* world) { _sceneWorld = world; };

};


#endif // __LEVEL_SCENE_H__