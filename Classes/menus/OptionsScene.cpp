#include "OptionsScene.h"
#include <SonarFrameworks.h>
#include "MainMenuScene.h"
#include <utils/Definitions.h>
#include <utils/Store.h>
#include <AudioEngine.h>

USING_NS_CC;
OptionsScene* OptionsScene::optionsMenuInstance = nullptr;
Scene* OptionsScene::scene = nullptr;

// Singleton 
OptionsScene* OptionsScene::getInstance()
{
	if (optionsMenuInstance == nullptr)
	{
		scene = Scene::create();
		optionsMenuInstance = new OptionsScene();
		optionsMenuInstance = create();
		scene->addChild(optionsMenuInstance);
	}
	return optionsMenuInstance;
}

Scene* OptionsScene::createScene() {

	optionsMenuInstance = OptionsScene::getInstance();
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

	Sprite* const background = Sprite::create(BACKGROUND);
	background->setPosition(Vec2(origin.x + screenZize.width / 2, origin.y + screenZize.height / 2));

	// Place buttons
	Button* buttonBack = Button::create(BUTTON_BACK_TO_MAIN_MENU, BUTTON_BACK_TO_MAIN_MENU);
	buttonBack->setPosition(Vec2(screenZize.width / 1.5 + origin.x, screenZize.height * 0.25 + origin.y));
	

	slider = ui::Slider::create();
	slider->loadBarTexture("buttons/slider.png");
	slider->loadSlidBallTextureNormal("buttons/thumb.png");
	slider->setPosition(Vec2(screenZize.width / 1.5, screenZize.height * 0.38));
	slider->setPercent(DEFAULT_VOLUME * 100);
	slider->addEventListener(CC_CALLBACK_2(OptionsScene::sliderEvent, this));
	_volume = DEFAULT_VOLUME;


	this->addChild(background);
	this->addChild(slider);
	this->addChild(buttonBack);

	buttonBack->addTouchEventListener(CC_CALLBACK_2(OptionsScene::onClickBackButton, this));

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

void OptionsScene::sliderEvent(Ref* sender, ui::Slider::EventType eventType) {

	if (eventType == ui::Slider::EventType::ON_PERCENTAGE_CHANGED) 
	{
		 slider = dynamic_cast<ui::Slider *> (sender);
		const int percent = slider->getPercent();
		_volume = float(percent)/100.0f;
		cocos2d::experimental::AudioEngine::setVolume(0, _volume);
	}
}

float OptionsScene::getVolume() {
	return _volume;
}