#include "LevelSelectionScene.h"
#include "Definitions.h"
#include <SonarFrameworks.h>

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
	  
	Size const screenZize = Director::getInstance()->getVisibleSize();
	Vec2 const origin = Director::getInstance()->getVisibleOrigin();

	// Place buttons
	Sprite* const title = Sprite::create(TITLE);
	title->setPosition(Vec2(screenZize.width / 2 + origin.x, screenZize.height * 0.65 + origin.y));
		
	Button* const playButton = Button::create(BUTTON_PLAY, BUTTON_PLAY);
	playButton->setPosition(Vec2(screenZize.width / 4 + origin.x, screenZize.height * 0.38));
	
	Button* const backButton = Button::create(BUTTON_BACK, BUTTON_BACK);
	backButton->setPosition(Vec2(screenZize.width / 1.52 + origin.x, screenZize.height * 0.25 + origin.y));


	this->addChild(title);
	this->addChild(playButton);
	this->addChild(backButton);

	playButton->addTouchEventListener(CC_CALLBACK_2(LevelSelectionScene::onClickPlayButton, this));
	backButton->addTouchEventListener(CC_CALLBACK_2(LevelSelectionScene::onClickBackButton, this));


//	SonarCocosHelper::UI ui;
//	ui.AddAudioToggle(SOUND_ON_BUTTON, SOUND_ON_PRESSED_BUTTON, SOUND_OFF_BUTTON, SOUND_OFF_PRESSED_BUTTON, this, SonarCocosHelper::UIButtonPosition::eBottomRight);

	return true;
}

void LevelSelectionScene::onClickPlayButton(Ref *sender, Widget::TouchEventType type){
	switch (type) {
		
	case Widget::TouchEventType::ENDED:
		//SwitchToGameScene(0.5);
		break;

	default:
		break;
	}
}


void LevelSelectionScene::onClickBackButton(Ref* sender, Widget::TouchEventType type) {
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