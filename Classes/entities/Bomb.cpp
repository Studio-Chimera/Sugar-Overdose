#include "Bomb.h"

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
