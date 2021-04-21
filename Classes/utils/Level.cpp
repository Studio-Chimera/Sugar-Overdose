#include "Level.h"
#include <iostream>
#include <vector>
#include "Store.h"
#include "PlayerHelper.h"
#include <proj.win32/PhysicsShapeCache.h>

using namespace cocos2d;

Scene* Level::scene()
{
    // 'scene' is an autorelease object
    Scene* scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
    // 'layer' is an autorelease object
    Level* level = Level::create();
    level->createPhysicalWorld(scene->getPhysicsWorld());
    scene->addChild(level);

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

    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);

    auto edgeNode = Node::create();
    edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    edgeNode->setPhysicsBody(edgeBody);

    this->addChild(edgeNode);


    auto store = Store::GetInstance();
    _tileMap = new TMXTiledMap();
    _tileMap->initWithTMXFile(store->g_mapName);
    // find layer (from tmx file)
    _background = _tileMap->layerNamed("background");

    auto playerHelper = new PlayerHelper();

    //get spawnpoint object from objects
    TMXObjectGroup* spawnPoints = _tileMap->objectGroupNamed("spawns");
    auto spawn1 = spawnPoints->objectNamed("spawn 1");
    auto spawn2 = spawnPoints->objectNamed("spawn 2");

    // spawn players
    /*auto player1 = playerHelper->createPlayer(new Vec2(spawn1.at("x").asInt(), spawn1.at("y").asInt()));
    auto player2 = playerHelper->createPlayer(new Vec2(spawn2.at("x").asInt(), spawn2.at("y").asInt()));*/
    auto player1 = playerHelper->createPlayer(new Vec2(200, 200), TYPE_PLAYER_ONE);
    auto player2 = playerHelper->createPlayer(new Vec2(400, 400), TYPE_PLAYER_TWO);
    
    // Load shapes
    auto shapeCache = PhysicsShapeCache::getInstance();
    /*shapeCache->addShapesWithFile("Shapes.plist");
    shapeCache->setBodyOnSprite("player1_stand", player1->getSprite());
    shapeCache->setBodyOnSprite("player2_stand", player2->getSprite());*/

    player1->getSprite()->getPhysicsBody()->setCollisionBitmask(1);
    player2->getSprite()->getPhysicsBody()->setCollisionBitmask(2);
    
    // add the node to scene tree
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

        //physicsBodyA->setVelocityLimit(0.1f);
        //physicsBodyA->setLinearDamping(1.0f);
        //physicsBodyA->setAngularDamping(1.0f);

        //physicsBodyB->setVelocityLimit(0.1f);
        //physicsBodyB->setLinearDamping(1.0f);
        //physicsBodyB->setAngularDamping(1.0f);
        //physicsBodyB->setAngularDamping(1.0f);

        //CCLOG("COLLISIONS HAS OCCURED");
        // 

        
        Node* playerB = physicsBodyB->getOwner();
        Vec2 positionPlayerB = playerB->getPosition();
        float positionPlayerBX = positionPlayerB.x;

        Node* playerA = physicsBodyA->getOwner();
        Size sizeA = playerA->getContentSize();
        Vec2 positionPlayerA = playerA->getPosition();

        float contact_AX = positionPlayerA.x - STEP_PLAYER + sizeA.width; // Take off 35 cause of step character which is 35px

        // Contact from left side, compute if player is in range of hitbox (+ or - STEP_PLAYER)
        if (contact_AX >= (positionPlayerBX - STEP_PLAYER) && contact_AX <= (positionPlayerBX + STEP_PLAYER)) {
            float newPositionX = positionPlayerA.x - STEP_PLAYER;
            Vec2 newPosition(newPositionX, positionPlayerA.y);
            physicsBodyA->getOwner()->setPosition(newPosition);
        } 
        
        // Contact from bot side
        else { 
            float newPositionY = positionPlayerA.y - STEP_PLAYER;
            Vec2 newPosition(positionPlayerA.x, newPositionY);
            physicsBodyA->getOwner()->setPosition(newPosition);
        }

        physicsBodyA->getOwner()->stopAllActions();
        physicsBodyA->applyForce(Vec2(0.0f, 0.0f), Vec2(0.0f, 0.0f));


        // Contact from right side

        // Contact from top side


        //physicsBodyA->resetForces();
        //physicsBodyB->resetForces();
        
    }

    return true;
}
