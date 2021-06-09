#include "SplashScene.h"
#include "SimpleAudioEngine.h"
#include "utils/Definitions.h"
#include "MainMenuScene.h"
#include <SonarFrameworks.h>

USING_NS_CC;

Scene* SplashScene::createScene()
{
    auto scene = Scene::create();
    auto layer = SplashScene::create();
    scene->addChild(layer);

    return scene;
}

bool SplashScene::init()
{
    if (!Layer::init())
    {
        return false;
    }

    SonarCocosHelper::UI::AddCentredBackground(SPLASH_SCENE, this);
    scheduleOnce(schedule_selector(SplashScene::SwitchToMainMenu), TIME_DISPLAY_SPLASH_SCENE);

    return true;
}

void SplashScene::SwitchToMainMenu(float dt)
{
        Scene* scene = MainMenuScene::createScene();
        TransitionFade* transition = TransitionFade::create(dt, scene);
        Director::getInstance()->pushScene(transition);
}
