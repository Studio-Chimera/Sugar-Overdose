#include "Definitions.h"

void changeScene(float dt, CustomScenes customScenes)
{
	Scene* newScene;
	switch (customScenes)
	{
	case(CustomScenes::MainMenu):
		newScene = MainMenuScene::createScene();
		break;
		/*return newScene;*/

	case(CustomScenes::LevelSelectionMenu):
		newScene = LevelSelectionScene::createScene();
		break;
	case(CustomScenes::OptionsMenu):
		newScene = OptionsScene::createScene();
		break;

	case(CustomScenes::CreditsMenu):
		newScene = CreditsScene::createScene();
		break;

	default:
		break; // Implement error msg
	}

	TransitionFade* transition = TransitionFade::create(dt, newScene);
	Director::getInstance()->replaceScene(newScene);
	
}
