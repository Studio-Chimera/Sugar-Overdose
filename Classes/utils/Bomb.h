#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class Bomb : public cocos2d::Sprite
{
    public:
        Bomb();
        ~Bomb();
        static Bomb* create();
        int x;
        int y;

    private:
        virtual bool init();
        void setBPosition(Vec2 position); 
};
