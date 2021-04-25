#pragma once
#ifndef __LEVEL_SCENE_H__
#define __LEVEL_SCENE_H__
#include "cocos2d.h"
#include "utils/Definitions.h"

using namespace cocos2d;

class Level : public Layer
{
private:
    CCTMXTiledMap* _tileMap;
    TMXLayer* _background;
    TMXLayer* _walls;
    TMXLayer* _border;

    PhysicsWorld* _sceneWorld;

    CCPoint tileCoordForPosition(CCPoint position);

    void createPhysicalWorld(PhysicsWorld* world) { _sceneWorld = world; };
    

public:
    virtual bool init();
    static Scene* scene();
    
    bool onContactBegin(PhysicsContact& contact); // detects collisions
    bool onContactPreSolve(PhysicsContact& contact, PhysicsContactPreSolve& solve); // detects collisions
    void onContactPostSolve(PhysicsContact& contact, const PhysicsContactPostSolve& solve); // detects collisions
    
    void setPlayerPosition(CCPoint position);

    void playersCollision(PhysicsBody* physicsBodyA, PhysicsBody* physicsBodyB);

    void playerCollisionBorderMap(PhysicsBody* physicsBodyA, PhysicsBody* physicsBodyB);


    // implement the "static create()" method manually
    CREATE_FUNC(Level);
};
#endif // __LEVEL_SCENE_H__