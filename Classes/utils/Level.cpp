#include "./Classes/utils/Level.h"
#include <iostream>
#include <vector>
#include "store.h"
using namespace cocos2d;
Scene* Level::scene()
{
    // 'scene' is an autorelease object
    Scene* scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    // 'layer' is an autorelease object
    Level* layer = Level::create();
    layer->createPhysicalWorld(scene->getPhysicsWorld());
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool Level::init()
{
    // ###################################################
    // Instanciate tilemap
    // ###################################################
    if (!Layer::init())
    {
        return false;
    }

    _tileMap = new TMXTiledMap();
    _tileMap->initWithTMXFile(g_mapName);
    // pickup tiles
    _background = _tileMap->layerNamed("background");
    // add the node to scene tree
    this->addChild(_tileMap);

    return true;
}
