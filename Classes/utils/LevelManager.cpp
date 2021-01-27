#include "LevelManager.h"
#include "Level.h"
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

	//Todo: Uncomment when adding Level Class
	auto level = new Level();
	auto scene = level->scene();
	std::stringstream map;
	map << "maps/" << level << ".tmx";
	level->setTiledMap(map.str());
	director->runWithScene(scene);
}
