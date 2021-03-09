#pragma once
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "utils/Definitions.h"
#include "utils/LevelManager.h"
#include <string>
#include <list>

USING_NS_CC;
using namespace ui;
using namespace std;

class LevelSelectionScene : public cocos2d::Layer{

public:

	// FUNC
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(LevelSelectionScene)

	// ATTR

private:

	// FUNC
	void onClickPlayButton(Ref* sender, Widget::TouchEventType touchEventType);
	void onClickBackButton(Ref* sender, Widget::TouchEventType touchEventType);

	// ATTR
	LevelManager* levelManager;
	list<string> listLevels;
	/*********** FOR BUTTONS TEXTS HARD-CODED ***********/
	//Label* label = Label::createWithTTF("Any", "fonts/Sugar Bomb.ttf", 45);

};