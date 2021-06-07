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
    
    customTiledPositionOfItems.push_back(Vec2(4, 3));
    customTiledPositionOfItems.push_back(Vec2(10, 1));
    customTiledPositionOfItems.push_back(Vec2(6, 2));
    customTiledPositionOfItems.push_back(Vec2(10, 4));

    int id = 1;
    string id_s = to_string(id);
    stringstream powerUp_RangeX;
    stringstream powerUp_RangeY;
    powerUp_RangeX << "PowerUp_RangeX";
    powerUp_RangeY << "PowerUp_RangeY";
    ValueMap spawnPowerUpRange;

    powerRangeVector = vector<PowerUP_Range*>();
    for (int i = 1; i < spawnPowerUp->getObjects().size() - 1; i++) {
        powerUp_RangeX << i;
        spawnPowerUpRange = spawnPowerUp->objectNamed(powerUp_RangeX.str());
        powerRangeVector.push_back(new PowerUP_Range(Vec2(spawnPowerUpRange.at("x").asFloat(), spawnPowerUpRange.at("y").asFloat()), customTiledPositionOfItems.front(), AXIS_X, 1));
        customTiledPositionOfItems.erase(customTiledPositionOfItems.begin());
        powerUp_RangeX.str("");
        powerUp_RangeX.clear();
        powerUp_RangeX << "PowerUp_RangeX";

        powerUp_RangeY << i;
        spawnPowerUpRange = spawnPowerUp->objectNamed(powerUp_RangeY.str());
        powerRangeVector.push_back(new PowerUP_Range(Vec2(spawnPowerUpRange.at("x").asFloat(), spawnPowerUpRange.at("y").asFloat()), customTiledPositionOfItems.front(), AXIS_Y, 1));
        customTiledPositionOfItems.erase(customTiledPositionOfItems.begin());
        powerUp_RangeY.str("");
        powerUp_RangeY.clear();
        powerUp_RangeY << "PowerUp_RangeY";
    }

    // set items case
    stringstream powerUp_RangeX_case;
    stringstream powerUp_RangeY_case;
    powerUp_RangeX_case << "powerUp_RangeX";
    powerUp_RangeY_case << "powerUp_RangeY";

    for (auto powerUp : powerRangeVector) {
        if (powerUp->getAxis() == AXIS_X) {
            customTiledMap->at(powerUp->getCustomTiledPosition().x).at(powerUp->getCustomTiledPosition().y) = powerUp_RangeX_case.str();
        }
        else if (powerUp->getAxis() == AXIS_Y) {
            customTiledMap->at(powerUp->getCustomTiledPosition().x).at(powerUp->getCustomTiledPosition().y) = powerUp_RangeY_case.str();
        }
    }

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

    for (auto powerUp : powerRangeVector) {
        this->addChild(powerUp->getSprite());
    }

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
        for (auto powerUp : powerRangeVector) {
            if (powerUp->getCustomTiledPosition().x == nextTiledPosition.x && powerUp->getCustomTiledPosition().y == nextTiledPosition.y){
                powerUp->getSprite()->removeFromParent();
            }
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
