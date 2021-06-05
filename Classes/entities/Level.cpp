#include "Level.h"
#include <iostream>
#include <vector>
#include "utils/Store.h"
#include "helpers/PlayerHelper.h"
#include "PowerUP_Range.h"
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

    mapWidth = tileMap->getMapSize().width;
    mapHeight = tileMap->getMapSize().height;

    fillCustomTiledMap();

    // prepare powerUP
    TMXObjectGroup* spawnPowerUp = tileMap->objectGroupNamed("PowerUp");
    
    //int id = 1;
    //string id_s = to_string(id);
    //for (auto spawnPowerUp : spawnPowerUp->objectNamed("PowerUp_RangeX" + id_s)) {
    //    if (spawnPowerUp.first.empty() == false) {
    //        spawnsVector->pushBack(spawnPowerUp);
    //        id += 1;
    //        id_s = to_string(id);
    //    }
    //}

    auto spawnPowerUpRangeX1 = spawnPowerUp->objectNamed("PowerUp_RangeX1");
    auto spawnPowerUpRangeX2 = spawnPowerUp->objectNamed("PowerUp_RangeX2");
    auto spawnPowerUpRangeY1 = spawnPowerUp->objectNamed("PowerUp_RangeY1");
    auto spawnPowerUpRangeY2 = spawnPowerUp->objectNamed("PowerUp_RangeY2");
    
    //for ()
    //powerRangeVector
    PowerUP_Range* powerUp_RangeX1 = new PowerUP_Range(Vec2(spawnPowerUpRangeX1.at("x").asFloat(), spawnPowerUpRangeX1.at("y").asFloat()), Vec2(4, 3), AXIS_X, 4);
    PowerUP_Range* powerUp_RangeX2 = new PowerUP_Range(Vec2(spawnPowerUpRangeX2.at("x").asFloat(), spawnPowerUpRangeX2.at("y").asFloat()), Vec2(6, 2), AXIS_X, 4);
    PowerUP_Range* powerUp_RangeY1 = new PowerUP_Range(Vec2(spawnPowerUpRangeY1.at("x").asFloat(), spawnPowerUpRangeY1.at("y").asFloat()), Vec2(10, 1), AXIS_Y, 4);
    PowerUP_Range* powerUp_RangeY2 = new PowerUP_Range(Vec2(spawnPowerUpRangeY2.at("x").asFloat(), spawnPowerUpRangeY2.at("y").asFloat()), Vec2(10, 4), AXIS_Y, 4);
       
    // set items case
    stringstream powerUp_RangeX_case;
    stringstream powerUp_RangeY_case;
    powerUp_RangeX_case << "powerUp_RangeX";
    powerUp_RangeY_case << "powerUp_RangeY";
  
    customTiledMap->at(powerUp_RangeX1->getCustomTiledPosition().x).at(powerUp_RangeX1->getCustomTiledPosition().y) = powerUp_RangeX_case.str();
    customTiledMap->at(powerUp_RangeX2->getCustomTiledPosition().x).at(powerUp_RangeX2->getCustomTiledPosition().y) = powerUp_RangeX_case.str();
    customTiledMap->at(powerUp_RangeY1->getCustomTiledPosition().x).at(powerUp_RangeY1->getCustomTiledPosition().y) = powerUp_RangeY_case.str();
    customTiledMap->at(powerUp_RangeY2->getCustomTiledPosition().x).at(powerUp_RangeY2->getCustomTiledPosition().y) = powerUp_RangeY_case.str();

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
    customTiledMap->at(player1->getCustomTiledPosition().x).at(player1->getCustomTiledPosition().y) = player1_case.str();
    customTiledMap->at(player2->getCustomTiledPosition().x).at(player2->getCustomTiledPosition().y) = player2_case.str();
    
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
    Create the whole custom tiled map
*/
void Level::fillCustomTiledMap() {

    customTiledMap = new vector<vector<string>>; // 2D dynamics array
    vector<string> currentColMap;

    for (int i = 0; i < mapWidth; i++) {
        for (int y = 0; y < mapHeight; y++) { // fill columns first

            if (tilesWalls->getTileGIDAt(Vec2(i, y)) != 0) {
                currentColMap.push_back("Wall");
            }
            else if (tilesBorders->getTileGIDAt(Vec2(i, y)) != 0) {
                currentColMap.push_back("Border");
            }
            else {
                currentColMap.push_back("Empty");
            }
        }
        
        if (!currentColMap.empty()) {
            customTiledMap->push_back(currentColMap);
            currentColMap.clear();
        }
    }
}

/*
    uses new player positions on all objects to detect collisions
*/
bool Level::checkIfCollisions(Vec2 nextTiledPosition, int direction, Player* player)
{
    string tile = customTiledMap->at(nextTiledPosition.x).at(nextTiledPosition.y);
    
    // collision
    if (tile != "Empty" && tile.substr(0, 7) != "powerUp") {
        return true;
    }

    // gather power-up
    else if (tile.substr(0, 7) == "powerUp") {
        if (tile == "powerUp_RangeX") {
            player->incrementRangeExplosionX(1);
        }
        else if (tile == "powerUp_RangeY") {
            player->incrementRangeExplosionY(1);
        }            
        customTiledMap->at(nextTiledPosition.x).at(nextTiledPosition.y) = "Empty";
    }
    
    return false; // no collison
}

/*
    place player on custom tiled map
*/
void Level::setNewPositionPlayerOnCustomTiledMap(Vec2 nextTiledPosition, int direction, int playerNumber){

    stringstream newCase;
    newCase << "Player_" << playerNumber;
    customTiledMap->at(nextTiledPosition.x).at(nextTiledPosition.y) = newCase.str();
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
        customTiledMap->at(oldTiledPosition).at(nextTiledPosition.y) = "Empty";
        return;

    case DIRECTION_RIGHT:
        oldTiledPosition = nextTiledPosition.x - 1;
        customTiledMap->at(oldTiledPosition).at(nextTiledPosition.y) = "Empty";
        return;

    case DIRECTION_TOP:
        oldTiledPosition = nextTiledPosition.y + 1;
        customTiledMap->at(nextTiledPosition.x).at(oldTiledPosition) = "Empty";
        return;

    case DIRECTION_BOTTOM:
        oldTiledPosition = nextTiledPosition.y - 1;
        customTiledMap->at(nextTiledPosition.x).at(oldTiledPosition) = "Empty";
        return;

    default:
        return;
    }
}
