#include "LevelManager.h"
#include "Level.h"
#include "store.h"

std::string g_mapName;

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

	auto instanceLevel = new Level();
	auto scene = instanceLevel->scene();
	std::stringstream map;
	map << "maps/" << level << ".tmx";
	instanceLevel->setTiledMap(map.str());
	director->runWithScene(scene);
}