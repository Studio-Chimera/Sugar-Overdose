#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace ui;

class MainMenuScene : public cocos2d::Layer {

public:

	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(MainMenuScene);
	static MainMenuScene* getInstance();
	
	MainMenuScene(MainMenuScene& other) = delete; // ??
	void operator=(const MainMenuScene&) = delete; // ??

	static void changeCurrentMusic(int newMusicId);

private:

	
	MainMenuScene() {};
	void onClickSelectionLevelButton(Ref* sender, Widget::TouchEventType touchEventType);
	void onClickOptionsButton(Ref* sender, Widget::TouchEventType touchEventType);
	void onClickCreditsButton(Ref* sender, Widget::TouchEventType touchEventType);
	void onClickLeaveButton(Ref* sender, Widget::TouchEventType touchEventType);

	static int currentMusicId;
	static MainMenuScene* mainMenuInstance;
	static Scene* scene;

};