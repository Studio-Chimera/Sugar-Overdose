#include "OptionsScene.h"
#include <SonarFrameworks.h>
#include "MainMenuScene.h"
#include <utils/Definitions.h>
#include <utils/Store.h>
#include <AudioEngine.h>

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
	
	ui::Slider* slider = ui::Slider::create();
	slider->loadBarTexture("buttons/slider.png");
	slider->loadSlidBallTextureNormal("buttons/thumb.png");
	slider->setPosition(Vec2(screenZize.width / 3, screenZize.height * 0.38));
	slider->addEventListener(CC_CALLBACK_2(OptionsScene::sliderEvent, this));	
	slider->setPercent(DEFAULT_VOLUME * 100);

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
		const ui::Slider *slider = dynamic_cast<ui::Slider *> (sender);
		const int percent = slider->getPercent();
		const float volume = float(percent)/100.0f;
		cocos2d::experimental::AudioEngine::setVolume(0, volume);
	}
}