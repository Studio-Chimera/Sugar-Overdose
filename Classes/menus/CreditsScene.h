#pragma once
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "utils/Definitions.h"

USING_NS_CC;

using namespace ui;

class CreditsScene : public cocos2d::Layer{

public:

	// FUNC
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(CreditsScene)

	// ATTR

private:

	// FUNC
	void onClickBackButton(Ref* sender, Widget::TouchEventType touchEventType);

	// ATTR

};