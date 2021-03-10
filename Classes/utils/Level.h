#pragma once
#ifndef __LEVEL_SCENE_H__
#define __LEVEL_SCENE_H__
#include "cocos2d.h"
using namespace cocos2d;

class Level : public Layer
{
private:
    TMXTiledMap* _tileMap;
    TMXLayer* _background;
    TMXLayer* _blocks;
    void createPhysicalWorld(PhysicsWorld* world) { _sceneWorld = world; };
    PhysicsWorld* _sceneWorld;

public:
    virtual bool init();
    static Scene* scene();

    // implement the "static create()" method manually
    CREATE_FUNC(Level);
};
#endif // __LEVEL_SCENE_H__