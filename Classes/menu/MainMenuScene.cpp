#include "MainMenuScene.h"
#include "Definitions.h"
#include <SonarFrameworks.h>

USING_NS_CC;

Scene* MainMenuScene::createScene() {

	auto scene = Scene::create();
	auto layer = MainMenuScene::create();

	scene->addChild(layer);

	return scene;
}
//
///*
//init sprites and buttons
//*/
//bool MainMenuScene::init() {
//	if (!Layer::init()) {	
//		return false;
//	} 
//	  
//	Size const screenZize = Director::getInstance()->getVisibleSize();
//	Vec2 const origin = Director::getInstance()->getVisibleOrigin();
//	
//	Sprite *title = Sprite::create(TITLE);
//	title->setPosition(Vec2(screenZize.width / 2 + origin.x, screenZize.height * 0.85 + origin.y));
//
//	Button *playButton = Button::create(PLAY_BUTTON, PLAY_PRESSED_BUTTON);
//	playButton->setPosition(Vec2(screenZize.width / 2 + origin.x, screenZize.height * 0.5));
//
//	Button *leaveButton = Button::create(LEAVE_BUTTON, LEAVE_PRESSED_BUTTON);
//	leaveButton->setPosition(Vec2(screenZize.width / 2 + origin.x, screenZize.height * 0.25 + origin.y));
//
//	this->addChild(title);
//	this->addChild(playButton);
//	this->addChild(leaveButton);
//
//	playButton->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::clickEvent, this));
//
//	SonarCocosHelper::UI ui;
//	ui.AddAudioToggle(SOUND_ON_BUTTON, SOUND_ON_PRESSED_BUTTON, SOUND_OFF_BUTTON, SOUND_OFF_PRESSED_BUTTON, this, SonarCocosHelper::UIButtonPosition::eBottomRight);
//
//	return true;
//}
//
//void MainMenuScene::clickEvent(Ref *sender, Widget::TouchEventType type){
//	switch (type) {
//		
//	case Widget::TouchEventType::ENDED:
//		SwitchToGameScene(0.5);
//		break;
//
//	default:
//		break;
//	}
//}
//
//void MainMenuScene::SwitchToGameScene(float dt)
//{
//	Scene* gameScene = GameScene::createScene();
//	TransitionFade* transition = TransitionFade::create(dt, gameScene);
//	Director::getInstance()->replaceScene(gameScene);
//}