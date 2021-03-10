#include "LevelManager.h"
#include "Level.h"
#include "Store.h"

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
	auto scene = Level::scene();
	director->runWithScene(scene);
}
