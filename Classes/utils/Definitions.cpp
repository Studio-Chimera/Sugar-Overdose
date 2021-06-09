#include "Definitions.h"

void changeScene(float dt, CustomScenes customScenes)
{	
	switch (customScenes)
	{
	case(CustomScenes::MainMenu):
		Director::getInstance()->pushScene(MainMenuScene::createScene());
		break;

	case(CustomScenes::LevelSelectionMenu):
		Director::getInstance()->pushScene(LevelSelectionScene::createScene());
		break;

	case(CustomScenes::OptionsMenu):
		Director::getInstance()->pushScene(OptionsScene::createScene());
		break;

	case(CustomScenes::CreditsMenu):
		Director::getInstance()->pushScene(CreditsScene::createScene());
		break;

	default:
		break; // Implement error msg
	}
}
