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

    Level(Level& other) = delete;
    static Level* getInstance();

    virtual bool init();
    static Scene* scene();
    bool onContactBegin(PhysicsContact& contact); // detects collisions
    bool onContactPreSolve(PhysicsContact& contact); // detects collisions
    
    Vector<TMXLayer*> getLayersLevel();
    int getTileGid(Vec2 position);
    Vec2 Level::getTileCoordForPosition(Vec2 position);

    // implement the "static create()" method manually
    CREATE_FUNC(Level);

protected:
    Level(){}
    ~Level(){}

private:

    static Level* levelInstance;
    static std::mutex mutex;

    TMXTiledMap* _tileMap;
    TMXLayer* _background;
    TMXLayer* _walls;
    PhysicsWorld* _sceneWorld;

    void createPhysicalWorld(PhysicsWorld* world) { _sceneWorld = world; };

};


#endif // __LEVEL_SCENE_H__