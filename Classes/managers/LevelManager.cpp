#include "LevelManager.h"
#include "entities/Level.h"
#include "utils/Store.h"

USING_NS_CC;

// ###################################################
// Declarations
// ###################################################

LevelManager::LevelManager()
{
	_levels = { "Classic", "River" };
}

LevelManager::~LevelManager()
{
}

// ###################################################
// Getters
// ###################################################

std::list<std::string> LevelManager::getLevels()
{
	return _levels;
}

// ###################################################
// Setters
// ###################################################


// ###################################################
// Methods
// ###################################################

void LevelManager::openLevel(std::string level)
{
	auto director = Director::getInstance();

	std::stringstream map;
	map << "maps/" << level << ".tmx";
	auto store = Store::GetInstance();
	store->g_mapName = map.str();
	
	//Level* currentLevel = Level::getInstance();
	auto scene = Level::getInstance()->scene(); /* Instantiate the Level singleton AND the Scene */
	director->replaceScene(scene);
}
