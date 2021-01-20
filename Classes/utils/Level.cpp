#include "./Classes/utils/Level.h"
#include <iostream>
#include <vector>
using namespace cocos2d;
Scene* Level::scene()
{
    // 'scene' is an autorelease object
    Scene* scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    // 'layer' is an autorelease object
    Level* layer = Level::create();
    layer->createPhysicalWorld(scene->getPhysicsWorld());
    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
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
    return true;
}

void Level::setTiledMap(std::string map)
{
    // instanciate a new tiledMap with level.tmx as model
    _tileMap = new TMXTiledMap();
    _tileMap->initWithTMXFile(map);
    // pickup tiles
    _background = _tileMap->layerNamed("background");
    _blocks = _tileMap->layerNamed("blocks");
    // add the node to scene tree
    this->addChild(_tileMap);
}