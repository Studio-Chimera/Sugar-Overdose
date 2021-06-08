#include "MainMenuScene.h"
#include "LevelSelectionScene.h"
#include "OptionsScene.h"
#include "utils/Definitions.h"
#include <SonarFrameworks.h>
#include <AudioEngine.h>

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

	// Get informations for display 
	Size const screenZize = Director::getInstance()->getVisibleSize();
	Vec2 const origin = Director::getInstance()->getVisibleOrigin();
	
	Sprite* const background = Sprite::create(BACKGROUND);
	background->setPosition(Vec2(origin.x + screenZize.width / 2, origin.y + screenZize.height / 2));
		
	// Place buttons
	Button* const buttonLevelSelection = Button::create(BUTTON_LEVEL_SELECTION, BUTTON_LEVEL_SELECTION);
	buttonLevelSelection->setPosition(Vec2(screenZize.width / 4 + origin.x, screenZize.height * 0.38));

	Button* const buttonOptions = Button::create(BUTTON_OPTIONS, BUTTON_OPTIONS);
	buttonOptions->setPosition(Vec2(screenZize.width / 1.5 + origin.x, screenZize.height * 0.38 + origin.y));

	Button* const buttonCredits = Button::create(BUTTON_CREDITS, BUTTON_CREDITS);
	buttonCredits->setPosition(Vec2(screenZize.width / 4.1 + origin.x, screenZize.height * 0.25 + origin.y));

	Button* const buttonLeave = Button::create(BUTTON_LEAVE, BUTTON_LEAVE);
	buttonLeave->setPosition(Vec2(screenZize.width / 1.52 + origin.x, screenZize.height * 0.25 + origin.y));


	this->addChild(background);
	this->addChild(buttonLevelSelection);
	this->addChild(buttonOptions);
	this->addChild(buttonCredits);
	this->addChild(buttonLeave);

	buttonLevelSelection->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::onClickSelectionLevelButton, this));
	buttonOptions->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::onClickOptionsButton, this));
	buttonCredits->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::onClickCreditsButton, this));
	buttonLeave->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::onClickLeaveButton, this));

	return true;
}

void MainMenuScene::onClickSelectionLevelButton(Ref *sender, Widget::TouchEventType type){
	switch (type) {
		
	case Widget::TouchEventType::ENDED:
		changeScene(1, CustomScenes::LevelSelectionMenu);
		break;

	default:
		break;
	}
}

void MainMenuScene::onClickOptionsButton(Ref* sender, Widget::TouchEventType type) {
	switch (type) {

	case Widget::TouchEventType::ENDED:
		changeScene(1, CustomScenes::OptionsMenu);
		break;

	default:
		break;
	}
}

void MainMenuScene::onClickCreditsButton(Ref* sender, Widget::TouchEventType type) {
	switch (type) {

	case Widget::TouchEventType::ENDED:
		changeScene(1, CustomScenes::CreditsMenu);
		break;

	default:
		break;
	}
}

void MainMenuScene::onClickLeaveButton(Ref* sender, Widget::TouchEventType type) {
	switch (type) {

	case Widget::TouchEventType::ENDED:
		cocos2d::experimental::AudioEngine::end();

		const auto director = Director::getInstance();
		director->end();
		break;
	}
}