#include "OptionsScene.h"
#include <SonarFrameworks.h>
#include "MainMenuScene.h"
#include <utils/Definitions.h>
USING_NS_CC;

Scene* OptionsScene::createScene() {

	auto scene = Scene::create();
	auto layer = OptionsScene::create();

	scene->addChild(layer);

	return scene;
}

/*
init sprites and buttons
*/
bool OptionsScene::init() {
	if (!Layer::init()) {	
		return false;
	} 
	
	// Place elements in menu
	Size const screenZize = Director::getInstance()->getVisibleSize();
	Vec2 const origin = Director::getInstance()->getVisibleOrigin();

	Sprite* const title = Sprite::create(TITLE);
	title->setPosition(Vec2(screenZize.width / 2 + origin.x, screenZize.height * 0.65 + origin.y));
	this->addChild(title);


	// Place buttons
	Button* buttonBack = Button::create(BUTTON_BACK_TO_MAIN_MENU, BUTTON_BACK_TO_MAIN_MENU);
	buttonBack->setPosition(Vec2(screenZize.width / 1.5 + origin.x, screenZize.height * 0.38 + origin.y));

	this->addChild(buttonBack);

	buttonBack->addTouchEventListener(CC_CALLBACK_2(OptionsScene::onClickBackButton, this));

//	SonarCocosHelper::UI ui;
//	ui.AddAudioToggle(SOUND_ON_BUTTON, SOUND_ON_PRESSED_BUTTON, SOUND_OFF_BUTTON, SOUND_OFF_PRESSED_BUTTON, this, SonarCocosHelper::UIButtonPosition::eBottomRight);

	return true;
}

void OptionsScene::onClickBackButton(Ref* sender, Widget::TouchEventType type) {
	switch (type) {

	case Widget::TouchEventType::ENDED:
		changeScene(1, CustomScenes::MainMenu);
		break;

	default:
		break;	
	}
}