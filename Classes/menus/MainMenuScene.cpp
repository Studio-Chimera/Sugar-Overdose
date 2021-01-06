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

/*
init sprites and buttons
*/
bool MainMenuScene::init() {
	if (!Layer::init()) {	
		return false;
	} 
	  
	Size const screenZize = Director::getInstance()->getVisibleSize();
	Vec2 const origin = Director::getInstance()->getVisibleOrigin();
	
	Sprite* const title = Sprite::create(TITLE);
	title->setPosition(Vec2(screenZize.width / 2 + origin.x, screenZize.height * 0.65 + origin.y));
		
	// Place buttons
	Button* const levelSelectionButton = Button::create(BUTTON_LEVEL_SELECTION, BUTTON_LEVEL_SELECTION);
	levelSelectionButton->setPosition(Vec2(screenZize.width / 4 + origin.x, screenZize.height * 0.38));

	Button* const optionsButton = Button::create(BUTTON_OPTIONS, BUTTON_OPTIONS);
	optionsButton->setPosition(Vec2(screenZize.width / 1.5 + origin.x, screenZize.height * 0.38 + origin.y));

	Button* const creditsButton = Button::create(BUTTON_CREDITS, BUTTON_CREDITS);
	creditsButton->setPosition(Vec2(screenZize.width / 4.1 + origin.x, screenZize.height * 0.25 + origin.y));

	Button* const leaveButton = Button::create(BUTTON_LEAVE, BUTTON_LEAVE);
	leaveButton->setPosition(Vec2(screenZize.width / 1.52 + origin.x, screenZize.height * 0.25 + origin.y));


	this->addChild(title);
	this->addChild(levelSelectionButton);
	this->addChild(optionsButton);
	this->addChild(creditsButton);
	this->addChild(leaveButton);

	levelSelectionButton->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::onClickSelectionLevelButton, this));
	optionsButton->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::onClickOptionsButton, this));
	creditsButton->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::onClickCreditsButton, this));
	leaveButton->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::onClickLeaveButton, this));


//	SonarCocosHelper::UI ui;
//	ui.AddAudioToggle(SOUND_ON_BUTTON, SOUND_ON_PRESSED_BUTTON, SOUND_OFF_BUTTON, SOUND_OFF_PRESSED_BUTTON, this, SonarCocosHelper::UIButtonPosition::eBottomRight);

	return true;
}

void MainMenuScene::onClickSelectionLevelButton(Ref *sender, Widget::TouchEventType type){
	switch (type) {
		
	case Widget::TouchEventType::ENDED:
		//SwitchToGameScene(0.5);
		break;

	default:
		break;
	}
}

void MainMenuScene::onClickOptionsButton(Ref* sender, Widget::TouchEventType type) {
	switch (type) {

	case Widget::TouchEventType::ENDED:
		//SwitchToGameScene(0.5);
		break;

	default:
		break;
	}
}

void MainMenuScene::onClickCreditsButton(Ref* sender, Widget::TouchEventType type) {
	switch (type) {

	case Widget::TouchEventType::ENDED:
		//SwitchToGameScene(0.5);
		break;

	default:
		break;
	}
}

void MainMenuScene::onClickLeaveButton(Ref* sender, Widget::TouchEventType type) {
	switch (type) {

	case Widget::TouchEventType::ENDED:
		auto director = Director::getInstance();
		director->end();
		break;

	//default:
	//	break;
	}
}
//
//void MainMenuScene::SwitchToGameScene(float dt)
//{
//	Scene* gameScene = GameScene::createScene();
//	TransitionFade* transition = TransitionFade::create(dt, gameScene);
//	Director::getInstance()->replaceScene(gameScene);
//}