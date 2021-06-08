#include "CreditsScene.h"
#include <SonarFrameworks.h>
#include "MainMenuScene.h"
#include <utils/Definitions.h>
USING_NS_CC;

Scene* CreditsScene::createScene() {

	auto scene = Scene::create();
	auto layer = CreditsScene::create();

	scene->addChild(layer);

	return scene;
}

/*
init sprites and buttons
*/
bool CreditsScene::init() {
	if (!Layer::init()) {	
		return false;
	}
	
	// Place elements in menu
	Size const screenZize = Director::getInstance()->getVisibleSize();
	Vec2 const origin = Director::getInstance()->getVisibleOrigin();

	Sprite* const background = Sprite::create(BACKGROUND);
	background->setPosition(Vec2(origin.x + screenZize.width / 2, origin.y + screenZize.height / 2));

	Sprite* const credits = Sprite::create(CREDITS);
	credits->setPosition(Vec2(screenZize.width / 1.5 + origin.x, screenZize.height * 0.64 + origin.y));
	
	// Place buttons
	Button* buttonBack = Button::create(BUTTON_BACK_TO_MAIN_MENU, BUTTON_BACK_TO_MAIN_MENU);
	buttonBack->setPosition(Vec2(screenZize.width / 1.5 + origin.x, screenZize.height * 0.25 + origin.y));

	
	this->addChild(background);
	this->addChild(credits);
	this->addChild(buttonBack);

	buttonBack->addTouchEventListener(CC_CALLBACK_2(CreditsScene::onClickBackButton, this));

	return true;
}

void CreditsScene::onClickBackButton(Ref* sender, Widget::TouchEventType type) {
	switch (type) {

	case Widget::TouchEventType::ENDED:
		changeScene(1, CustomScenes::MainMenu);
		break;

	default:
		break;	
	}
}