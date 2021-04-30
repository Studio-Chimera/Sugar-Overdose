#include "Level.h"
#include <iostream>
#include <vector>
#include "utils/Store.h"
#include "helpers/PlayerHelper.h"
#include <proj.win32/PhysicsShapeCache.h>

using namespace cocos2d;

Scene* Level::scene()
{
    // 'scene' is an autorelease object
    Scene* scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    //scene->getPhysicsWorld()->setGravity(Vec2(0.0f, 0.0f));

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

    // get map properties
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    // create border map edgeNode
    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 1);
    edgeBody->setCollisionBitmask(1); // Set a tag
    edgeBody->setContactTestBitmask(true); // Allow to collision to be detected
    edgeBody->setDynamic(false);

    auto edgeNode = Node::create();
    
    edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    edgeNode->setPhysicsBody(edgeBody);
    edgeNode->setOpacity(0);


    // init map
    auto store = Store::GetInstance();
    _tileMap = new TMXTiledMap();
    _tileMap->initWithTMXFile(store->g_mapName);

    // find layer (from tmx file)
    _background = _tileMap->layerNamed("background");
    _walls = _tileMap->layerNamed("walls");
    _border = _tileMap->layerNamed("borders");
    Value customProperty = _border->getProperty("collisionable");
    
    auto playerHelper = new PlayerHelper();

    // get spawnpoint object from objects
    TMXObjectGroup* spawnPoints = _tileMap->objectGroupNamed("spawns");
    auto spawn1 = spawnPoints->objectNamed("spawn 1");
    auto spawn2 = spawnPoints->objectNamed("spawn 2");

    // spawn players
    /*auto player1 = playerHelper->createPlayer(new Vec2(spawn1.at("x").asInt(), spawn1.at("y").asInt()));
    auto player2 = playerHelper->createPlayer(new Vec2(spawn2.at("x").asInt(), spawn2.at("y").asInt()));*/
    auto player1 = playerHelper->createPlayer(new Vec2(200, 200), TYPE_PLAYER_ONE);
    auto player2 = playerHelper->createPlayer(new Vec2(400, 400), TYPE_PLAYER_TWO);
    
    player1->getSprite()->getPhysicsBody()->setCollisionBitmask(1);
    player2->getSprite()->getPhysicsBody()->setCollisionBitmask(2);
    
    // add the nodes to scene tree
    this->addChild(_tileMap);
    this->addChild(player1->getSprite());
    this->addChild(player2->getSprite());
    this->addChild(edgeNode);

    // get & set players controls 
    EventListenerKeyboard *player1Controller = std::get<EventListenerKeyboard*>(player1->getController());
    EventListenerKeyboard *player2Controller = std::get<EventListenerKeyboard*>(player2->getController());

    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(player1Controller, player1->getSprite());
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(player2Controller, player2->getSprite());

    // enable collision detection
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(Level::onContactBegin, this);
    contactListener->onContactPreSolve = CC_CALLBACK_2(Level::onContactPreSolve, this);
    contactListener->onContactPostSolve = CC_CALLBACK_2(Level::onContactPostSolve, this);

    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    return true;
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
        playersCollision(physicsBodyA, physicsBodyB);
    }
    else if (physicsBodyA->getCollisionBitmask() == 1 && physicsBodyB->getCollisionBitmask() == 2) 
    {
        playerCollisionBorderMap(physicsBodyA, physicsBodyB);
    }
    return true;
}

bool Level::onContactPreSolve(PhysicsContact& contact, PhysicsContactPreSolve& solve) {

    PhysicsBody* physicsBodyA = contact.getShapeA()->getBody();
    PhysicsBody* physicsBodyB = contact.getShapeB()->getBody();
    //CCLOG(physicsBodyA->getNode()->isRunning() ? "a true" : " a false");
    //CCLOG(physicsBodyB->getNode()->isRunning() ? " b true" : " b false");

    //ssize_t sizeA = physicsBodyA->getNode()->getNumberOfRunningActions();
    //CCLOG("%d : ", sizeA);
    
    //physicsBodyA->getOwner()->cleanup();

    //ssize_t sizeA_2 = physicsBodyA->getNode()->getNumberOfRunningActions();
    //CCLOG("%d : ", sizeA_2);

    /*physicsBodyA->setVelocity(Vec2(0.0f, 0.0f));
    physicsBodyA->setMoment(0.0f);
    physicsBodyA->applyForce(Vec2(0.0f, 0.0f), Vec2(0.0f, 0.0f));
    physicsBodyA->resetForces();

    physicsBodyB->setVelocity(Vec2(0.0f, 0.0f));
    physicsBodyB->setMoment(0.0f);
    physicsBodyB->applyForce(Vec2(0.0f, 0.0f), Vec2(0.0f, 0.0f));
    physicsBodyB->resetForces();*/

    //solve.setFriction(0.0f);
    //solve.setRestitution(0.0f);
    //solve.setSurfaceVelocity(Vec2(0.0f, 0.0f));
    
    CCLOG("COLLISIONS HAS OCCURED PreSolve");
    return true;
}

/**
* Start calcul
*/
void Level::onContactPostSolve(PhysicsContact& contact, const PhysicsContactPostSolve& solve) {
    
    PhysicsBody* physicsBodyA = contact.getShapeA()->getBody();
    PhysicsBody* physicsBodyB = contact.getShapeB()->getBody();

    /*physicsBodyA->setVelocity(Vec2(0.0f, 0.0f));
    physicsBodyA->setMoment(0.0f);
    physicsBodyA->applyForce(Vec2(0.0f, 0.0f), Vec2(0.0f, 0.0f));
    physicsBodyA->resetForces();

    physicsBodyB->setVelocity(Vec2(0.0f, 0.0f));
    physicsBodyB->setMoment(0.0f);
    physicsBodyB->applyForce(Vec2(0.0f, 0.0f), Vec2(0.0f, 0.0f));
    physicsBodyB->resetForces();*/

    CCLOG("solve.getFriction() : %d ", solve.getFriction());
    CCLOG("solve.getRestitution() : %d ", solve.getRestitution());
    CCLOG("solve.getSurfaceVelocity().x : %d ", solve.getSurfaceVelocity().x);
    CCLOG("solve.getSurfaceVelocity().y : %d ", solve.getSurfaceVelocity().y);

    CCLOG("physicsBodyA->getPosition().x: %d ", physicsBodyA->getPosition().x);
    CCLOG("physicsBodyA->getPosition().y: %d ", physicsBodyA->getPosition().y);
    CCLOG("COLLISIONS HAS OCCURED PostSolve");
}


/*
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


void Level::playerCollisionBorderMap(PhysicsBody* physicsBodyA, PhysicsBody* physicsBodyB){
    
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    float maxWidthBorder = Director::getInstance()->getOpenGLView()->getDesignResolutionSize().width;
    float maxHeightBorder = Director::getInstance()->getOpenGLView()->getDesignResolutionSize().height;
    float borderLeft = origin.x + STEP_PLAYER * 3;
    float borderRight = maxWidthBorder - STEP_PLAYER * 3;
    float borderTop = maxHeightBorder - STEP_PLAYER * 4;
    float borderBottom = origin.y + STEP_PLAYER * 4;

    Node* player = physicsBodyB->getNode();
    Size sizePlayer = player->getContentSize();
    Vec2 positionPlayer = physicsBodyB->getPosition();

    // Contact on left border 
    if (positionPlayer.x <= borderLeft) {
        Vec2 currentPositon = physicsBodyB->getOwner()->getPosition();
        currentPositon.x = currentPositon.x + STEP_PLAYER;
        physicsBodyB->getOwner()->setPosition(currentPositon);
    
    // Contact on right border 
    } else if (positionPlayer.x >= borderRight) {
        Vec2 currentPositon = physicsBodyB->getOwner()->getPosition();
        currentPositon.x = currentPositon.x - STEP_PLAYER;
        physicsBodyB->getOwner()->setPosition(currentPositon);
    
    // Contact on top border 
    }
    else if (positionPlayer.y >= borderTop) {
        Vec2 currentPositon = physicsBodyB->getOwner()->getPosition();
        currentPositon.y = currentPositon.y - STEP_PLAYER;
        physicsBodyB->getOwner()->setPosition(currentPositon);

        // Contact on bottom border
    } else if (positionPlayer.y <= borderBottom) {
        Vec2 currentPositon = physicsBodyB->getOwner()->getPosition();
        currentPositon.y = currentPositon.y + STEP_PLAYER;
        physicsBodyB->getOwner()->setPosition(currentPositon);
    }   
}

//Point Level::tileCoordForPosition(CCPoint position)
//{
//    int x = position.x / _tileMap->getTileSize().width;
//    int y = ((_tileMap->getMapSize().height * _tileMap->getTileSize().height) - position.y) / _tileMap->getTileSize().height;
//    return ccp(x, y);
//}


//void Level::setPlayerPosition(CCPoint position)
//{
//    CCPoint tileCoord = this->tileCoordForPosition(position);
//    int tileGid = _border->tileGIDAt(tileCoord);
//    if (tileGid) {
//        CCDictionary* properties = _tileMap->propertiesForGID(tileGid);
//        if (properties) {
//            CCString* collision = new CCString();
//            *collision = *properties->valueForKey("collisionable");
//            if (collision && (collision->compare("True") == 0)) {
//                return;
//            }
//        }
//    }
//    _player->setPosition(position);
//}
