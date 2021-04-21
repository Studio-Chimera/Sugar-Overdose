#include "Level.h"
#include <iostream>
#include <vector>
#include "Store.h"
#include "PlayerHelper.h"

using namespace cocos2d;

Scene* Level::scene()
{
    // 'scene' is an autorelease object
    Scene* scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
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
/*
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);

    auto edgeNode = Node::create();
    edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    edgeNode->setPhysicsBody(edgeBody);

    this->addChild(edgeNode);
*/

    //if (!Level::initWithPhysics())
    //{

    //}

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
    auto player2 = playerHelper->createPlayer(new Vec2(300, 300), TYPE_PLAYER_TWO);
    /*player1->getSprite()->getPhysicsBody()->setCollisionBitmask(1);
    */player2->getSprite()->getPhysicsBody()->setCollisionBitmask(2);
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

    // Enable collision detection
    auto contactListener2 = EventListenerPhysicsContact::create();
    contactListener2->onContactPostSolve = CC_CALLBACK_1(Level::onContactPreSolve, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener2, this);

    return true;
}

bool Level::onContactPreSolve(PhysicsContact& contact) {


    PhysicsBody* physicsBodyShapeA = contact.getShapeA()->getBody();
    PhysicsBody* physicsBodyShapeB = contact.getShapeB()->getBody();
    if ((1 == physicsBodyShapeA->getCollisionBitmask() && 2 == physicsBodyShapeB->getCollisionBitmask()) ||
        (2 == physicsBodyShapeA->getCollisionBitmask() && 1 == physicsBodyShapeB->getCollisionBitmask()) ||
        (2 == physicsBodyShapeA->getCollisionBitmask() && 2 == physicsBodyShapeB->getCollisionBitmask()))
    {
        physicsBodyShapeA;
        physicsBodyShapeB;
        CCLOG("COLLISIONS HAS OCCURED PRESOLVE");
    }
    return true;

}

/*
* detects collisions
*/
bool Level::onContactBegin(PhysicsContact& contact) {
    
    PhysicsBody* physicsBodyShapeA = contact.getShapeA()->getBody(); // A is who create the conctact
    PhysicsBody* physicsBodyShapeB = contact.getShapeB()->getBody(); // B is who is undergo contact
    
    // check if the bodies have collided
    // 2 => player
    // 1 => border (not setted)
    if ((1 == physicsBodyShapeA->getCollisionBitmask() && 2 == physicsBodyShapeB->getCollisionBitmask()) ||
        (2 == physicsBodyShapeA->getCollisionBitmask() && 1 == physicsBodyShapeB->getCollisionBitmask()) || 
        (2 == physicsBodyShapeA->getCollisionBitmask() && 2 == physicsBodyShapeB->getCollisionBitmask()))
    {

        //physicsBodyShapeA->setVelocityLimit(0.1f);
        //physicsBodyShapeA->setLinearDamping(1.0f);
        //physicsBodyShapeA->setAngularDamping(1.0f);

        //physicsBodyShapeB->setVelocityLimit(0.1f);
        //physicsBodyShapeB->setLinearDamping(1.0f);
        //physicsBodyShapeB->setAngularDamping(1.0f);
        //physicsBodyShapeB->setAngularDamping(1.0f);

        //CCLOG("COLLISIONS HAS OCCURED");

        
        Node* playerB = physicsBodyShapeB->getOwner();
        Vec2 positionPlayerB = playerB->getPosition();
        float positionPlayerBX = positionPlayerB.x;

        Node* playerA = physicsBodyShapeA->getOwner();
        Size sizeA = playerA->getContentSize();
        Vec2 positionPlayerA = playerA->getPosition();

        float contact_AX = positionPlayerA.x - 45 + sizeA.width; // Take off 35 cause of step character which is 35px

        // Contact from left side
        if (contact_AX >= (positionPlayerBX - 50) && contact_AX <= (positionPlayerBX + 50)) {
            float newPositionX = positionPlayerA.x - 15;
            Vec2 newPosition(newPositionX, positionPlayerA.y);
            physicsBodyShapeA->getOwner()->setPosition(newPosition);
        } 
        
        // Contact from bot side
        else { 
            float newPositionY = positionPlayerA.y - 15;
            Vec2 newPosition(positionPlayerA.x, newPositionY);
            physicsBodyShapeA->getOwner()->setPosition(newPosition);
        }

        physicsBodyShapeA->getOwner()->stopAllActions();


        // Contact from right side

        // Contact from top side


        physicsBodyShapeA->resetForces();
        physicsBodyShapeB->resetForces();
        
    }

    return true;
}
