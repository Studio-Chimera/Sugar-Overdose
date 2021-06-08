#include "LevelSelectionScene.h"
#include <SonarFrameworks.h>
#include "MainMenuScene.h"
#include "utils/Definitions.h"
#include <AudioEngine.h>
#include <AudioEngine.h>

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

	Sprite* const background = Sprite::create(BACKGROUND);
	background->setPosition(Vec2(origin.x + screenZize.width / 2, origin.y + screenZize.height / 2));

	//Todo: Refactor with dynamic text
	/*********** WAY WITH BUTTON TEXT HARD-CODED ***********/
	
	// With this way, we need a black background in image

	/*Button* buttonPlay = Button::create();
	Label* labelPlay = Label::createWithTTF("play", "fonts/Sugar Bomb.ttf", 45);
	buttonPlay->setPosition(Vec2(screenZize.width / 4 + origin.x, screenZize.height * 0.3));
	buttonPlay->addChild(labelPlay);
	labelPlay->setString("STOP");

	Button* buttonBack = Button::create();
	Label* labelBack = Label::createWithTTF("back to main menu", "fonts/Sugar Bomb.ttf", 45);
	auto size = labelBack->getContentSize();
	buttonBack->setContentSize(size);
	buttonBack->setPosition(Vec2(screenZize.width / 1.5 + origin.x, screenZize.height * 0.35));
	buttonBack->addChild(labelBack); */

	/*********** WAY WITH BUTTONS TEXTS HARD-CODED ***********/

	// Place buttons
	Button* buttonLevel1 = Button::create(BUTTON_LEVEL1, BUTTON_LEVEL1);
	buttonLevel1->setPosition(Vec2(screenZize.width / 1.5 + origin.x, screenZize.height * 0.64));
	Button* buttonLevel2 = Button::create(BUTTON_LEVEL2, BUTTON_LEVEL2);
	buttonLevel2->setPosition(Vec2(screenZize.width / 1.5 + origin.x, screenZize.height * 0.51));
	Button* buttonLevel3 = Button::create(BUTTON_LEVEL3, BUTTON_LEVEL3);
	buttonLevel3->setPosition(Vec2(screenZize.width / 1.5 + origin.x, screenZize.height * 0.38));

	Button* buttonBack = Button::create(BUTTON_BACK_TO_MAIN_MENU, BUTTON_BACK_TO_MAIN_MENU);
	buttonBack->setPosition(Vec2(screenZize.width / 1.5 + origin.x, screenZize.height * 0.25 + origin.y));
	
	//Todo: Add level selection
	//for each (level in levelManager->getLevels()) {
	//	// add image level
	//	// add name 
	//}

	buttonLevel1->addTouchEventListener(CC_CALLBACK_2(LevelSelectionScene::onClickPlayButton, this, MAP_BLUE));
	buttonLevel2->addTouchEventListener(CC_CALLBACK_2(LevelSelectionScene::onClickPlayButton, this, MAP_MANY_WALL));
	buttonLevel3->addTouchEventListener(CC_CALLBACK_2(LevelSelectionScene::onClickPlayButton, this, MAP_TRIANGLE));
	buttonBack->addTouchEventListener(CC_CALLBACK_2(LevelSelectionScene::onClickBackButton, this));

	levelManager = new LevelManager();
	listLevels = levelManager->getLevels();

	this->addChild(background);
	this->addChild(buttonLevel1);
	this->addChild(buttonLevel2);
	this->addChild(buttonLevel3);
	this->addChild(buttonBack);
	return true;
}

void LevelSelectionScene::onClickPlayButton(Ref *sender, Widget::TouchEventType type, string level){
	
	runAction(DelayTime::create(TIME_START_GAME));

	switch (type) {
		
	case Widget::TouchEventType::ENDED:
		if (level == MAP_BLUE){
			levelManager->openLevel(MAP_BLUE);
			cocos2d::experimental::AudioEngine::play2d(SOUND_OPEN_LEVEL, false);
			cocos2d::experimental::AudioEngine::play2d(SOUND_LEVEL1, false);
		}
		else if (level == MAP_MANY_WALL) {
			levelManager->openLevel(MAP_MANY_WALL);
			cocos2d::experimental::AudioEngine::play2d(SOUND_OPEN_LEVEL, false);
			cocos2d::experimental::AudioEngine::play2d(SOUND_LEVEL2, false);
		}
		else if (level == MAP_TRIANGLE) {
			levelManager->openLevel(MAP_TRIANGLE);
			cocos2d::experimental::AudioEngine::play2d(SOUND_OPEN_LEVEL, false);
			cocos2d::experimental::AudioEngine::play2d(SOUND_LEVEL3, false);
		}
		
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
