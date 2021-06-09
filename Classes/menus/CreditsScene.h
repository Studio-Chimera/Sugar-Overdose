#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "utils/Definitions.h"

USING_NS_CC;

using namespace ui;

class CreditsScene : public Layer{

public:

	static CreditsScene* getInstance();
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(CreditsScene)

	CreditsScene(CreditsScene& other) = delete; // ??
	void operator=(const CreditsScene&) = delete; // ??

	
private:

	CreditsScene() {};
	void onClickBackButton(Ref* sender, Widget::TouchEventType touchEventType);
	
	static CreditsScene* creditsSceneInstance;
	static Scene* scene;

};