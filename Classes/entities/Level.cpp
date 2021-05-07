#include "Level.h"
#include <iostream>
#include <vector>
#include "utils/Store.h"
#include "helpers/PlayerHelper.h"
#include "entities/Player.h"
#include <proj.win32/PhysicsShapeCache.h>

using namespace cocos2d;

Level* Level::levelInstance = nullptr;
//std::mutex Level::mutex;

Level* Level::getInstance()
{
    //std::lock_guard<std::mutex> lock(mutex);
    if (levelInstance == nullptr)
    {
        levelInstance = new Level();
    }
    return levelInstance;
}

Scene* Level::scene()
{
    // 'scene' is an autorelease object
    Scene* scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
    // 'layer' is an autorelease object
    levelInstance = Level::getInstance()->create();
    levelInstance->createPhysicalWorld(scene->getPhysicsWorld());
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

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // create border
    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 1);
    auto edgeNode = Node::create();
    edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    edgeNode->setPhysicsBody(edgeBody);


    // prepare map
    auto store = Store::GetInstance();
    _tileMap = new TMXTiledMap();
    _tileMap->initWithTMXFile(store->g_mapName);

    // manage layers (from tmx file)
    _background = _tileMap->getLayer("background");
    _background->setTag(1);
    
    auto wallsBody = PhysicsBody::createEdgeBox(Size(STEP_PLAYER, STEP_PLAYER), PHYSICSBODY_MATERIAL_DEFAULT, 3);
    _walls = _tileMap->getLayer("walls");
    _walls->setTag(2);

    float mapWidth = _tileMap->getMapSize().width;
    float mapHeight = _tileMap->getMapSize().height;
    float tileWidth = _tileMap->getTileSize().width;
    float tileHeight = _tileMap->getTileSize().height;
    int gid;
    int currentPosInArray = 0;

    for (int i = 0; i < mapWidth; i++) {
        for (int y = 0; y < mapHeight; y++) {
            gid = _walls->getTileGIDAt(Vec2(i, y));
            if (gid) {
                float tileXPositon = i * tileWidth;
                float tileYPosition = (mapHeight * tileHeight) - ((y + 1) * tileHeight);
                Rect rect = Rect(tileXPositon, tileYPosition, tileWidth, tileHeight);
                //Node noude = Node();
                
                //noude.addChild(react);
                obstacles[currentPosInArray] = rect;
                currentPosInArray++;
            }
        }
    }
    
    //auto* eazeaz = _walls->getTiles
    auto *eazeaz = _walls->getTileSet();
    
    auto tileCoord = new Point(20, 20);
    Size* size = new Size(5, 5);
    Rect(*tileCoord, *size);

    //_walls->setPhysicsBody(wallsBody);
    
    // get spawnpoint objects from objects
    //TMXObjectGroup* spawnPoints = _tileMap->objectGroupNamed("spawns");
    //auto spawn1 = spawnPoints->objectNamed("spawn 1");
    //auto spawn2 = spawnPoints->objectNamed("spawn 2");

    // spawn players
    const auto playerHelper = new PlayerHelper();
    /*auto player1 = playerHelper->createPlayer(new Vec2(spawn1.at("x").asInt(), spawn1.at("y").asInt()));
    auto player2 = playerHelper->createPlayer(new Vec2(spawn2.at("x").asInt(), spawn2.at("y").asInt()));*/
    auto player1 = playerHelper->createPlayer(new Vec2(100, 100), TYPE_PLAYER_ONE, this);
    auto player2 = playerHelper->createPlayer(new Vec2(200, 200), TYPE_PLAYER_TWO, this);
    
    player1->getSprite()->getPhysicsBody()->setCollisionBitmask(1);
    player2->getSprite()->getPhysicsBody()->setCollisionBitmask(2);
    
    // add the node to scene tree
    this->addChild(edgeNode);
    this->addChild(_tileMap);
    this->addChild(player1->getSprite());
    this->addChild(player2->getSprite());

    EventListenerKeyboard *player1Controller = std::get<EventListenerKeyboard*>(player1->getController());
    EventListenerKeyboard *player2Controller = std::get<EventListenerKeyboard*>(player2->getController());

    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(player1Controller, player1->getSprite());
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(player2Controller, player2->getSprite());

    // Enable collision detection
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(Level::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

    //// Enable collision detection
    //auto contactListener2 = EventListenerPhysicsContact::create();
    //contactListener2->onContactPostSolve = CC_CALLBACK_1(Level::onContactPreSolve, this);
    //this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener2, this);

    return true;
}


/*
 return cocos2d-x coordonates, with tiled coordonates
*/
Sprite* Level::getTileCoordForPosition(Vec2 position, Size size)
{
    //int posX = position.x;
    float x = position.x / _tileMap->getTileSize().width;
    //int y = position.y / _tileMap->getTileSize().height;
    float y = ((_tileMap->getMapSize().height * _tileMap->getTileSize().height) - position.y) / _tileMap->getTileSize().height;
    //CCLOG("WALL x %f WALL y %f", x, y);
    //player1->getSprite()->getPhysicsBody()->getFirstShape()->
    Rect newReactangle = 
        Rect(position.x + 2 - size.width / 2, 
            position.y + 2 - size.height / 2,
            size.width - 4, size.height - 4);

    for (int i = 0; i < sizeof(obstacles); i++) {
        if (newReactangle.intersectsRect(obstacles[i])) {
            CCLOG("true");
        }
    }
    

    return _walls->getTileAt(Vec2(x, y));
    //return _walls->getTileAt(position);
}

bool Level::onContactPreSolve(PhysicsContact& contact) {


    PhysicsBody* physicsBodyA = contact.getShapeA()->getBody();
    PhysicsBody* physicsBodyB = contact.getShapeB()->getBody();
    if ((1 == physicsBodyA->getCollisionBitmask() && 2 == physicsBodyB->getCollisionBitmask()) ||
        (2 == physicsBodyA->getCollisionBitmask() && 1 == physicsBodyB->getCollisionBitmask()) ||
        (2 == physicsBodyA->getCollisionBitmask() && 2 == physicsBodyB->getCollisionBitmask()))
    {
        physicsBodyA;
        physicsBodyB;
        CCLOG("COLLISIONS HAS OCCURED PRESOLVE");
    }
    return true;

}

/*
* detects collisions
*/
bool Level::onContactBegin(PhysicsContact& contact) {
    
    PhysicsBody* physicsBodyA = contact.getShapeA()->getBody(); // A is who create the conctact
    PhysicsBody* physicsBodyB = contact.getShapeB()->getBody(); // B is who is undergo contact
    
    // check if the bodies have collided
    // 2 => player
    // 1 => border (not setted)
    if ((1 == physicsBodyA->getCollisionBitmask() && 2 == physicsBodyB->getCollisionBitmask()) ||
        (2 == physicsBodyA->getCollisionBitmask() && 1 == physicsBodyB->getCollisionBitmask()) || 
        (2 == physicsBodyA->getCollisionBitmask() && 2 == physicsBodyB->getCollisionBitmask()))
    {

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


        // Contact from left side, 
        if (xMaxPlayerA >= borderLeftPlayerB_MinRange && xMaxPlayerA <= borderLeftPlayerB_MaxRange) {
            float newPositionX = positionPlayerA.x - STEP_PLAYER;
            Vec2 newPosition(newPositionX, positionPlayerA.y);
            physicsBodyA->getOwner()->setPosition(newPosition);
        }
        
        // Contact from right side, 
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

        physicsBodyA->getOwner()->cleanup();
        return true;

        //physicsBodyA->setVelocity(Vec2(0.0f, 0.0f));
        //physicsBodyA->applyForce(Vec2(0.0f, 0.0f), Vec2(0.0f, 0.0f));
        //physicsBodyA->resetForces();
        
    }

    return true;
}


Vector<TMXLayer*> Level::getLayersLevel() {
    Vector<TMXLayer*> layersLevel;
    layersLevel.pushBack(_walls);
    layersLevel.pushBack(_background);
    return layersLevel;
}