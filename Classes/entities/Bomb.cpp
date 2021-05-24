#include "Bomb.h"

//bool Bomb::init()
//{
//    return true;
//}

Bomb::Bomb(){
    //Bomb* b_Sprite = new Bomb();

    _spriteCacher = SpriteFrameCache::getInstance();

    std::stringstream plistFile;
    plistFile << "sprites/bomb/bomb_.plist";
    _spriteCacher->addSpriteFramesWithFile(plistFile.str());

    std::stringstream standPng;
    standPng << "bomb2_reduced.png";
    this->_sprite = new Sprite;
    auto myfile = standPng.str();
    _sprite->initWithSpriteFrameName(myfile);
}

Bomb::~Bomb(){}

Sprite* Bomb::getSprite()
{
    return _sprite;
}

SpriteFrameCache* Bomb::getSpritecacher()
{
    return _spriteCacher;
}


Bomb* Bomb::create()
{
    
  
    
    //if (b_Sprite->initWithSpriteFrameName("/sprites/bomb/bomb1.png"))
    //{
    //    b_Sprite->init();

    //    b_Sprite->autorelease();

    //    return b_Sprite;
    //};
    //CC_SAFE_DELETE(b_Sprite);
    return nullptr;
}

void Bomb::setBPosition(Vec2 position)
{
    //setPosition(10, 10);
}
