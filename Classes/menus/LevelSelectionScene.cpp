#include "LevelSelectionScene.h"
#include <SonarFrameworks.h>
#include "MainMenuScene.h"
#include <utils/Definitions.h>
USING_NS_CC;

Scene* LevelSelectionScene::createScene() {

	auto scene = Scene::create();
	auto layer = LevelSelectionScene::create();

	scene->addChild(layer);

	return scene;
}

/*
init sprites and buttons
*/
bool LevelSelectionScene::init() {
	if (!Layer::init()) {	
		return false;
	} 
	
	// Place elements in menu
	Size const screenZize = Director::getInstance()->getVisibleSize();
	Vec2 const origin = Director::getInstance()->getVisibleOrigin();

	Sprite* const title = Sprite::create(TITLE);
	title->setPosition(Vec2(screenZize.width / 2 + origin.x, screenZize.height * 0.65 + origin.y));
	this->addChild(title);

	Button* buttonPlay = Button::create();
	Label* labelPlay = Label::createWithTTF("play", "fonts/Sugar Bomb.ttf", 45);
	buttonPlay->setPosition(Vec2(screenZize.width / 4 + origin.x, screenZize.height * 0.3));
	buttonPlay->addChild(labelPlay);
	
	labelPlay->setString("STOP");
	
	// CAPTURE est un fond noir, il faut trouer une solution pour un boutton sans img
	Button* buttonBack = Button::create();
	Label* labelBack = Label::createWithTTF("back to main menu", "fonts/Sugar Bomb.ttf", 45);
	auto size = labelBack->getContentSize();
	buttonBack->setContentSize(size);
	buttonBack->setPosition(Vec2(screenZize.width / 1.5 + origin.x, screenZize.height * 0.35));
	buttonBack->addChild(labelBack);

	//for each (level in levelManager->getLevels()) {
	//	// add image level
	//	// add name 
	//}

	this->addChild(buttonPlay);
	this->addChild(buttonBack);

	buttonPlay->addTouchEventListener(CC_CALLBACK_2(LevelSelectionScene::onClickPlayButton, this));
	buttonBack->addTouchEventListener(CC_CALLBACK_2(LevelSelectionScene::onClickBackButton, this));


//	SonarCocosHelper::UI ui;
//	ui.AddAudioToggle(SOUND_ON_BUTTON, SOUND_ON_PRESSED_BUTTON, SOUND_OFF_BUTTON, SOUND_OFF_PRESSED_BUTTON, this, SonarCocosHelper::UIButtonPosition::eBottomRight);

	return true;
}

void LevelSelectionScene::onClickPlayButton(Ref *sender, Widget::TouchEventType type){
	switch (type) {
		
	case Widget::TouchEventType::ENDED:
		//changeScene(1, CustomScenes::????);
		break;

	default:
		break;
	}
}


void LevelSelectionScene::onClickBackButton(Ref* sender, Widget::TouchEventType type) {
	switch (type) {

	case Widget::TouchEventType::ENDED:
		changeScene(1, CustomScenes::MainMenu);
		break;

	default:
		break;	
	}
}