#pragma once
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace ui;

class LevelSelectionScene : public cocos2d::Layer{

public:

	// FUNC
	static cocos2d::Scene* createScene();
	virtual bool init();
	//void SwitchToGameScene(float dt);
	CREATE_FUNC(LevelSelectionScene)

	// ATTR

private:

	// FUNC
	void onClickPlayButton(Ref* sender, Widget::TouchEventType touchEventType);
	void onClickBackButton(Ref* sender, Widget::TouchEventType touchEventType);

	// ATTR

};