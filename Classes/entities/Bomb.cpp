#include "Bomb.h"

bool Bomb::init()
{
    return true;
}

Bomb::Bomb()
{
}

Bomb::~Bomb()
{
}

Bomb* Bomb::create()
{
    Bomb* b_Sprite = new Bomb();

    if (b_Sprite && b_Sprite->initWithSpriteFrameName("/sprites/bomb/bomb1.png"))
    {
        b_Sprite->init();

        b_Sprite->autorelease();

        return b_Sprite;
    };
    CC_SAFE_DELETE(b_Sprite);
    return nullptr;
}

void Bomb::setBPosition(Vec2 position)
{
    //setPosition(10, 10);
}
