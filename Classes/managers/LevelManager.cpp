#include "LevelManager.h"
#include "entities/Level.h"
#include "helpers/PlayerHelper.h"
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
	std::stringstream map;
	map << "maps/" << level << ".tmx";
	auto store = Store::GetInstance();
	store->g_mapName = map.str();
	auto scene = Level::getInstance()->createScene(level); /* Instantiate the Level singleton AND the Scene */
	Director::getInstance()->pushScene(scene);
}
