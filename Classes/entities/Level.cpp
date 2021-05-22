#include "Level.h"
#include <iostream>
#include <vector>
#include "utils/Store.h"
#include "helpers/PlayerHelper.h"
#include "entities/Player.h"
#include <proj.win32/PhysicsShapeCache.h>

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

    int currentPosInWallsVector = 0;
    int currentPosInBordersVector = 0;
    float tileXPositon;
    float tileYPosition;
    obstaclesWalls = new Vector<Rect*>;
    obstaclesBorders = new Vector<Rect*>;

    for (int i = 0; i < mapWidth; i++) {
        for (int y = 0; y < mapHeight; y++) {
            wallGid = tilesWalls->getTileGIDAt(Vec2(i, y));
            borderGid = tilesBorders->getTileGIDAt(Vec2(i, y)); // CAN BE OPTIMISED
            

            if (wallGid != 0 || borderGid != 0) {
                tileXPositon = i * tileWidth;
                float tileYPositionOLD = (mapHeight * tileHeight) - ((y + 1) * tileHeight); // Check if calcul is good
                tileYPosition = y * tileHeight; // Check if calcul is good

                Rect* rect = new Rect(tileXPositon, tileYPosition, tileWidth, tileHeight);


                if (wallGid != 0) {
                    obstaclesWalls->insert(currentPosInWallsVector, rect);
                    currentPosInWallsVector++;
                }
                else if (borderGid != 0) {
                    obstaclesBorders->insert(currentPosInBordersVector, rect);
                    currentPosInBordersVector++;

                }

            }
        }
    }
        
    // get spawnpoint objects from objects
    TMXObjectGroup* spawnPoints = tileMap->objectGroupNamed("spawns");
    auto spawn1 = spawnPoints->objectNamed("spawn 1");
    auto spawn2 = spawnPoints->objectNamed("spawn 2");

    // spawn players
    const auto playerHelper = new PlayerHelper();
    auto player1 = playerHelper->createPlayer(new Vec2(spawn1.at("x").asInt(), spawn1.at("y").asInt()), TYPE_PLAYER_ONE, this);
    auto player2 = playerHelper->createPlayer(new Vec2(spawn2.at("x").asInt(), spawn2.at("y").asInt()), TYPE_PLAYER_TWO, this);

    
    // get & set players controls 
    EventListenerKeyboard *player1Controller = std::get<EventListenerKeyboard*>(player1->getController());
    EventListenerKeyboard *player2Controller = std::get<EventListenerKeyboard*>(player2->getController());

    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(player1Controller, player1->getSprite());
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(player2Controller, player2->getSprite());

    // enable collision detection
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(Level::onContactBegin, this);    
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

    // add nodes to scene tree
    //this->addChild(edgeNode);
    this->addChild(tileMap);
    this->addChild(player1->getSprite());
    this->addChild(player2->getSprite());

    return true;
}

/*
    uses rectangles on all objects to detect collisions
*/
bool Level::checkIfCollision(Vec2 nextPosition, Size sizePlayer)
{
    Rect newReactangle = Rect(nextPosition.x, nextPosition.y, sizePlayer.width, sizePlayer.height);
    
    int sizeObstaclesWalls = sizeof(obstaclesWalls);
    int sizeObstaclesBorders = sizeof(obstaclesBorders);

    for (int i = 0; i < sizeObstaclesWalls; i++) {
        if (newReactangle.intersectsRect(*obstaclesWalls->at(i))) {
            *obstaclesWalls->at(i);
            return true;
        }
    }
    for (int i = 0; i < sizeObstaclesBorders; i++) {
        if (newReactangle.intersectsRect(*obstaclesBorders->at(i))) {
            *obstaclesBorders->at(i);
            return true;
        }
    }

    return false;
}

/*
* detects collisions
* collisionBitmask 2 => players
* collisionBitmask 1 => border  
*/
bool Level::onContactBegin(PhysicsContact& contact) {
    
    PhysicsBody* physicsBodyA = contact.getShapeA()->getBody(); // A is who create the conctact
    PhysicsBody* physicsBodyB = contact.getShapeB()->getBody(); // B is who is undergo contact    

    // check if the bodies have collided
    if (physicsBodyA->getCollisionBitmask() == 2 && physicsBodyB->getCollisionBitmask() == 2)
    {
        //playersCollision(physicsBodyA, physicsBodyB);
    }
    return true;
}

/*
    detects collisions
 	when : collision have been trigger between 2 players
 	do : move back player which made the collision
*/
void Level::playersCollision(PhysicsBody* physicsBodyA, PhysicsBody* physicsBodyB) {
    Node* playerA = physicsBodyA->getOwner();
    Size sizeA = playerA->getContentSize();
    Vec2 positionPlayerA = playerA->getPosition();

    Node* playerB = physicsBodyB->getOwner();
    Size sizeB = playerB->getContentSize();
    Vec2 positionPlayerB = playerB->getPosition();

    float xMaxPlayerA = positionPlayerA.x + sizeA.width;
    float xMaxPlayerB = positionPlayerB.x + sizeB.width;
    float yMaxPlayerA = positionPlayerA.y + sizeA.height;
    float yMaxPlayerB = positionPlayerB.y + sizeB.height;

    // used to compute if player is in range of hitbox(~ + or - one STEP_PLAYER)
    float borderLeftPlayerB_MinRange = positionPlayerB.x - STEP_PLAYER;
    float borderLeftPlayerB_MaxRange = positionPlayerB.x + STEP_PLAYER;

    float borderRightPlayerB_MinRange = xMaxPlayerB - STEP_PLAYER;
    float borderRightPlayerB_MaxRange = xMaxPlayerB + STEP_PLAYER;

    float borderTopPlayerB_MinRange = yMaxPlayerB - STEP_PLAYER;
    float borderTopPlayerB_MaxRange = yMaxPlayerB + STEP_PLAYER;


    // Contact from left side
    if (xMaxPlayerA >= borderLeftPlayerB_MinRange && xMaxPlayerA <= borderLeftPlayerB_MaxRange) {
        float newPositionX = positionPlayerA.x - STEP_PLAYER;
        Vec2 newPosition(newPositionX, positionPlayerA.y);
        physicsBodyA->getOwner()->setPosition(newPosition);
    }

    // Contact from right side
    else if (positionPlayerA.x >= borderRightPlayerB_MinRange && positionPlayerA.x <= borderRightPlayerB_MaxRange) {
        float newPositionX = positionPlayerA.x + STEP_PLAYER;
        Vec2 newPosition(newPositionX, positionPlayerA.y);
        physicsBodyA->getOwner()->setPosition(newPosition);
    }

    // Contact from top side
    else if (positionPlayerA.y >= borderTopPlayerB_MinRange && positionPlayerA.y <= borderTopPlayerB_MaxRange) {
        float newPositionY = positionPlayerA.y + STEP_PLAYER;
        Vec2 newPosition(positionPlayerA.x, newPositionY);
        physicsBodyA->getOwner()->setPosition(newPosition);
    }

    // Contact from bot side
    else {
        float newPositionY = positionPlayerA.y - STEP_PLAYER;
        Vec2 newPosition(positionPlayerA.x, newPositionY);
        physicsBodyA->getOwner()->setPosition(newPosition);
    }
}
