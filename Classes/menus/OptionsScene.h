#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "utils/Definitions.h"

USING_NS_CC;
using namespace ui;

class OptionsScene : public Layer{

public:

	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(OptionsScene)

	static OptionsScene* getInstance();
	float getVolume();

	OptionsScene(OptionsScene& other) = delete; // ??
	void operator=(const OptionsScene&) = delete; // ??

private:

	OptionsScene() {};

	void onClickBackButton(Ref* sender, Widget::TouchEventType touchEventType);
	void sliderEvent(Ref* sender, ui::Slider::EventType eventType);

	static OptionsScene* optionsMenuInstance;
	static Scene* scene;
	float _volume;
	ui::Slider* slider;
};