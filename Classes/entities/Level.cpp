#include "Level.h"
#include <iostream>
#include <vector>
#include "utils/Store.h"
#include "helpers/PlayerHelper.h"
#include "entities/Player.h"
#include "entities/PowerUP_Range.h"
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

    tilesBackground = tileMap->getLayer("background");
    tilesWalls = tileMap->getLayer("walls");
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

    // prepare powerUP
    TMXObjectGroup* spawnPowerUp = tileMap->objectGroupNamed("PowerUp");
    auto spawnPowerUpRangeX1 = spawnPowerUp->objectNamed("PowerUp_RangeX1");
    auto spawnPowerUpRangeX2 = spawnPowerUp->objectNamed("PowerUp_RangeX2");
    auto spawnPowerUpRangeY1 = spawnPowerUp->objectNamed("PowerUp_RangeY1");
    auto spawnPowerUpRangeY2 = spawnPowerUp->objectNamed("PowerUp_RangeY2");
    
    PowerUP_Range* powerUp_RangeX1 = new PowerUP_Range(Vec2(spawnPowerUpRangeX1.at("x").asFloat(), spawnPowerUpRangeX1.at("y").asFloat()), Vec2(4, 3), AXIS_X, 1);
    PowerUP_Range* powerUp_RangeX2 = new PowerUP_Range(Vec2(spawnPowerUpRangeX2.at("x").asFloat(), spawnPowerUpRangeX2.at("y").asFloat()), Vec2(6, 2), AXIS_X, 1);
    PowerUP_Range* powerUp_RangeY1 = new PowerUP_Range(Vec2(spawnPowerUpRangeY1.at("x").asFloat(), spawnPowerUpRangeY1.at("y").asFloat()), Vec2(8, 1), AXIS_Y, 1);
    PowerUP_Range* powerUp_RangeY2 = new PowerUP_Range(Vec2(spawnPowerUpRangeY2.at("x").asFloat(), spawnPowerUpRangeY2.at("y").asFloat()), Vec2(4, 4), AXIS_Y, 1);
        
    // spawn players
    TMXObjectGroup* spawnPlayer = tileMap->objectGroupNamed("Spawns");
    auto spawn1 = spawnPlayer->objectNamed("Spawn 1");
    auto spawn2 = spawnPlayer->objectNamed("Spawn 2");

    const auto playerHelper = PlayerHelper::getInstance();
    auto player1 = playerHelper->createPlayer(mapHeight, new Vec2(spawn1.at("x").asFloat(), spawn1.at("y").asFloat()), PLAYER_NUMBER_ONE, this);
    auto player2 = playerHelper->createPlayer(mapHeight, new Vec2(spawn2.at("x").asFloat(), spawn2.at("y").asFloat()), PLAYER_NUMBER_TWO, this);
    
    // set players case
    stringstream player1_case;
    stringstream player2_case;
    player1_case << "Player_" << player1->getPlayerNumber();
    player2_case << "Player_" << player2->getPlayerNumber();
    float currY1 = player1->getCustomTiledPosition().y;
    float currY2 = player2->getCustomTiledPosition().y;
    map->at(player1->getCustomTiledPosition().x).at(player1->getCustomTiledPosition().y) = player1_case.str();
    map->at(player2->getCustomTiledPosition().x).at(player2->getCustomTiledPosition().y) = player2_case.str();
    
    // get & set players controls
    EventListenerKeyboard *player1Controller = std::get<EventListenerKeyboard*>(player1->getController());
    EventListenerKeyboard *player2Controller = std::get<EventListenerKeyboard*>(player2->getController());

    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(player1Controller, player1->getSprite());
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(player2Controller, player2->getSprite());

    // display map, players & powerUp
    if (tileMap) { this->addChild(tileMap); }
    if (player1) { this->addChild(player1->getSprite()); }
    if (player2) { this->addChild(player2->getSprite()); }
    if (powerUp_RangeX1) { this->addChild(powerUp_RangeX1->getSprite()); }
    if (powerUp_RangeX2) { this->addChild(powerUp_RangeX2->getSprite()); }
    if (powerUp_RangeY1) { this->addChild(powerUp_RangeY1->getSprite()); }
    if (powerUp_RangeY2) { this->addChild(powerUp_RangeY2->getSprite()); }

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
    
    return false;
}

void Level::setNewPositionPlayerOnCustomTiledMap(Vec2 nextTiledPosition, int direction, int playerNumber){

    stringstream newCase;
    newCase << "Player_" << playerNumber;
    map->at(nextTiledPosition.x).at(nextTiledPosition.y) = newCase.str();
    cleanOldPosition(nextTiledPosition, direction);
    return;
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
