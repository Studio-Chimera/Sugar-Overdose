#include "Level.h"
#include <iostream>
#include <vector>
#include "utils/Store.h"
#include "helpers/PlayerHelper.h"
#include "entities/Player.h"
#include <proj.win32/PhysicsShapeCache.h>
#include <external/bullet/include/bullet/LinearMath/btAlignedAllocator.h>
#include "Bomb.h"

using namespace cocos2d;

Level* Level::levelInstance = nullptr;

Level* Level::getInstance()
{
    if (levelInstance == nullptr)
    {
        levelInstance = new Level();
    }
    return levelInstance;
}

Vector<TMXLayer*> Level::getLayersLevel() 
{
    Vector<TMXLayer*> layersLevel;
    layersLevel.pushBack(tilesWalls);
    layersLevel.pushBack(tilesBackground);
    return layersLevel;
}

Scene* Level::scene()
{
    // 'scene' is an autorelease object
    Scene* scene = Scene::create();

    // 'layer' is an autorelease object
    levelInstance = Level::getInstance()->create();
    scene->addChild(levelInstance);

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

    // get map properties
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    // prepare map
    const auto store = Store::GetInstance();
    tileMap = new TMXTiledMap();
    tileMap->initWithTMXFile(store->g_mapName);

    // prepare background
    tilesBackground = tileMap->getLayer("background");
    
    // prepare walls (obstacles)
    tilesWalls = tileMap->getLayer("walls");

    // prepare borders
    tilesBorders = tileMap->layerNamed("borders");

    const float mapWidth = tileMap->getMapSize().width;
    const float mapHeight = tileMap->getMapSize().height;
    const float tileWidth = tileMap->getTileSize().width;
    const float tileHeight = tileMap->getTileSize().height;
    int wallGid = 0;
    int borderGid = 0;

    map = new vector<vector<string>>;
    vector<string> currentColMap;

    for (int i = 0; i < mapWidth; i++) {
        for (int y = 0; y < mapHeight; y++) {
            wallGid = tilesWalls->getTileGIDAt(Vec2(i, y));
            borderGid = tilesBorders->getTileGIDAt(Vec2(i, y)); // CAN BE OPTIMISED
            

            if (wallGid != 0 || borderGid != 0) {
                
                if (wallGid != 0) {
                    currentColMap.push_back("Wall");
                }

                else if (borderGid != 0) {
                    currentColMap.push_back("Border");
                }
            }
            else {
                currentColMap.push_back("Empty");
            }
        }
        
        if (!currentColMap.empty()) {
            map->push_back(currentColMap);
            currentColMap.clear();
        }
    }
        
    // get spawnpoint objects from objects
    TMXObjectGroup* spawnPoints = tileMap->objectGroupNamed("spawns");
    auto spawn1 = spawnPoints->objectNamed("spawn 1");
    auto spawn2 = spawnPoints->objectNamed("spawn 2");

    // spawn players
    const auto playerHelper = new PlayerHelper();
    auto player1 = playerHelper->createPlayer(new Vec2(spawn1.at("x").asFloat(), spawn1.at("y").asFloat()), TYPE_PLAYER_ONE, this);
    auto player2 = playerHelper->createPlayer(new Vec2(spawn2.at("x").asFloat(), spawn2.at("y").asFloat()), TYPE_PLAYER_TWO, this);
    
    map->at(player1->getCustomTiledPosition()->x).at(player1->getCustomTiledPosition()->y) = "Player";
    map->at(player2->getCustomTiledPosition()->x).at(player2->getCustomTiledPosition()->y) = "Player";

    
    // get & set players controls 
    EventListenerKeyboard *player1Controller = std::get<EventListenerKeyboard*>(player1->getController());
    EventListenerKeyboard *player2Controller = std::get<EventListenerKeyboard*>(player2->getController());

    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(player1Controller, player1->getSprite());
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(player2Controller, player2->getSprite());

    this->addChild(tileMap);
    this->addChild(player1->getSprite());
    this->addChild(player2->getSprite());

    return true;
}

/*
    uses new player positions on all objects to detect collisions
*/
bool Level::checkIfCollision(Vec2 nextTiledPosition, int direction)
{

    string tile = map->at(nextTiledPosition.x).at(nextTiledPosition.y);
    if (tile != "Empty") {
        return true;
    }
    
    map->at(nextTiledPosition.x).at(nextTiledPosition.y) = "Player";
    cleanOldPosition(nextTiledPosition, direction);
    return false;
}

/*
    called when player move to free old case and 
    permit to other players to come in this case
*/
void Level::cleanOldPosition(Vec2 nextTiledPosition, int direction) {
    
    float oldTiledPosition;
    switch (direction)
    {
    case DIRECTION_LEFT:
        oldTiledPosition = nextTiledPosition.x + 1;
        map->at(oldTiledPosition).at(nextTiledPosition.y) = "Empty";
        return;

    case DIRECTION_RIGHT:
        oldTiledPosition = nextTiledPosition.x - 1;
        map->at(oldTiledPosition).at(nextTiledPosition.y) = "Empty";
        return;

    case DIRECTION_TOP:
        oldTiledPosition = nextTiledPosition.y + 1;
        map->at(nextTiledPosition.x).at(oldTiledPosition) = "Empty";
        return;

    case DIRECTION_BOTTOM:
        oldTiledPosition = nextTiledPosition.y - 1;
        map->at(nextTiledPosition.x).at(oldTiledPosition) = "Empty";
        return;

    default:
        return;
    }
}