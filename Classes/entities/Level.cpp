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
    Scene* scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    //scene->getPhysicsWorld()->setGravity(Vec2(0.0f, 0.0f));

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

    // prepare map
    const auto store = Store::GetInstance();
    tileMap = new TMXTiledMap();
    tileMap->initWithTMXFile(store->g_mapName);

    // prepare background
    tilesBackground = tileMap->getLayer("background");
    //_background->setTag(1);
    
    // prepare walls (obstacles)
    tilesWalls = tileMap->getLayer("walls");
    //_walls->setTag(1);

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
                tileYPosition = (mapHeight * tileHeight) - ((y + 1) * tileHeight); // Check if calcul is good

                // set a physics body just for display and debug
                Rect* rect = new Rect(tileXPositon + STEP_PLAYER, tileYPosition + STEP_PLAYER * 2, tileWidth, tileHeight);
                //const auto obstacleBody = PhysicsBody::createBox(Size(STEP_PLAYER + 17, STEP_PLAYER + 17), PHYSICSBODY_MATERIAL_DEFAULT);
                const auto obstacleBody = PhysicsBody::createBox(Size(STEP_PLAYER * 2, STEP_PLAYER * 2), PHYSICSBODY_MATERIAL_DEFAULT);
                obstacleBody->setDynamic(false);

                Node* node = new Node();
                node->addComponent(obstacleBody);
                node->setPosition(Vec2(tileXPositon - 4, tileYPosition - 8));
                //node->setPosition(Vec2(tileXPositon  , tileYPosition));

                this->addChild(node);

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

    player1->getSprite()->getPhysicsBody()->setCollisionBitmask(2);
    player2->getSprite()->getPhysicsBody()->setCollisionBitmask(2);
    
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
    this->addChild(edgeNode);
    this->addChild(tileMap);
    this->addChild(player1->getSprite());
    this->addChild(player2->getSprite());

    return true;
}


/*
    DEPRECATED
    return cocos2d-x coordonates, with tiled coordonates
*/
//Sprite* Level::getTileCoordForPosition(Vec2 position, Size sizePlayer)
//{
//    float x = position.x / tileMap->getTileSize().width;
//    float y = ((tileMap->getMapSize().height * tileMap->getTileSize().height) - position.y) / tileMap->getTileSize().height;
//   
//    // missing code from commit 0091fbc - refacto(comments): clean code from useless comments
//    return tilesWalls->getTileAt(Vec2(x, y));
//}

/*
    uses rectangles on all objects to detect collisions
*/
bool Level::checkIfCollision(Vec2 nextPosition, Size sizePlayer)
{
    Rect newReactangle = Rect(nextPosition.x, nextPosition.y, sizePlayer.width, sizePlayer.height - 4);

    for (int i = 0; i < sizeof(obstaclesWalls); i++) {
        if (newReactangle.intersectsRect(*obstaclesWalls->at(i))) {
            *obstaclesWalls->at(i);
            return true;
        }
    }
    for (int i = 0; i < sizeof(obstaclesBorders); i++) {
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
        playersCollision(physicsBodyA, physicsBodyB);
    }
    else if (physicsBodyA->getCollisionBitmask() == 1 && physicsBodyB->getCollisionBitmask() == 2) 
    {
        //playerCollisionBorderMap(physicsBodyA, physicsBodyB);
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
        //physicsBodyA->setPositionOffset(Vec2(0.0, 0.0));
    }

    // Contact from right side
    else if (positionPlayerA.x >= borderRightPlayerB_MinRange && positionPlayerA.x <= borderRightPlayerB_MaxRange) {
        float newPositionX = positionPlayerA.x + STEP_PLAYER;
        Vec2 newPosition(newPositionX, positionPlayerA.y);
        physicsBodyA->getOwner()->setPosition(newPosition);
        //physicsBodyA->setPositionOffset(Vec2(0.0, 0.0));
    }

    // Contact from top side
    else if (positionPlayerA.y >= borderTopPlayerB_MinRange && positionPlayerA.y <= borderTopPlayerB_MaxRange) {
        float newPositionY = positionPlayerA.y + STEP_PLAYER;
        Vec2 newPosition(positionPlayerA.x, newPositionY);
        physicsBodyA->getOwner()->setPosition(newPosition);
        //physicsBodyA->setPositionOffset(Vec2(0.0, 0.0));
    }

    // Contact from bot side
    else {
        float newPositionY = positionPlayerA.y - STEP_PLAYER;
        Vec2 newPosition(positionPlayerA.x, newPositionY);
        physicsBodyA->getOwner()->setPosition(newPosition);
        //physicsBodyA->setPositionOffset(Vec2(0.0, 0.0));
    }
}

/*
    
*/
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
