#include "PlayerHelper.h"
#include <entities/Level.h>
#include <cmath>

USING_NS_CC;
// ###################################################
// Declarations
// ###################################################

PlayerHelper* PlayerHelper::playerHelperInstance = nullptr;

PlayerHelper::PlayerHelper()
{
    _playersInstances = {};
}

PlayerHelper::~PlayerHelper(){}


PlayerHelper* PlayerHelper::getInstance()
{
	if (playerHelperInstance == nullptr)
	{
		playerHelperInstance = new PlayerHelper();
	}
	return playerHelperInstance;
}

// ###################################################
// Getters
// ###################################################

std::list<Player*> PlayerHelper::getPlayers()
{
	return _playersInstances;
}

// ###################################################
// Setters
// ###################################################


// ###################################################
// Methods
// ###################################################

/*
	call this one to have your new player instance
	type arg is a const "TYPE_PLAYER_X"
*/
Player* PlayerHelper::createPlayer(float mapHeight, Vec2* position, int playerNumber, Level* level)
{
	//create player instance
    auto player = new Player;
	player->setPosition(*position);
	player->setPlayerNumber(playerNumber);

	player->setCustomTiledPosition(Vec2(trunc(player->getPosition().x / STEP_PLAYER), mapHeight - 1 - trunc(player->getPosition().y / STEP_PLAYER)));

	setPlayerSprites(player);

	// add players special 
    auto controllerHelper = new ControllerHelper;
	controllerHelper->addControls(player, playerNumber); //to use controls on scene add: this->_eventDispatcher->addEventListenerWithSceneGraphPriority(player->getController(), player->getSprite());

	// save instance
	_playersInstances.push_back(player);
    return player;
}

// add all the animation's frame to the player
void PlayerHelper::setPlayerSprites(Player* player)
{
	// search all the sprites
    auto playerNumber = _playersInstances.size();
	std::stringstream plistFile;
	plistFile << "sprites/player/player"<< playerNumber+1 << "/player" << playerNumber + 1 << ".plist";
	player->getSpritecacher()->addSpriteFramesWithFile(plistFile.str());
	
	// set all sprites
	std::stringstream standPng;
	standPng << "player" << playerNumber + 1 << "_stand.png";
	player->getSprite()->initWithSpriteFrameName(standPng.str());

	// create the animations with sprites
	createSideMoveAnimation(playerNumber, player);
	createTopMoveAnimation(playerNumber, player);
	createBottomMoveAnimation(playerNumber, player);

	player->getSprite()->setPosition(player->getPosition());
}

void PlayerHelper::createSideMoveAnimation(int playerNumber, Player* player)
{
	const int kNumberOfFrames = 2;
	Vector<SpriteFrame*> frames;
	for (int i = 1; i < kNumberOfFrames; i++)
	{
		std::stringstream ss;
		ss << "player" << playerNumber+1 << "_sideWalk0" << i << ".png";
		auto sprite = player->getSpritecacher()->getSpriteFrameByName(ss.str());
		frames.pushBack(sprite);
	}

	player->setSideMoveAnimation(frames);
}

void PlayerHelper::createTopMoveAnimation(int playerNumber, Player* player)
{
	const int kNumberOfFrames = 2;
	Vector<SpriteFrame*> frames;
	for (int i = 1; i < kNumberOfFrames; i++)
	{
		std::stringstream ss;
		ss << "player" << playerNumber + 1 << "_topWalk0" << i << ".png";
		auto sprite = player->getSpritecacher()->getSpriteFrameByName(ss.str());
		frames.pushBack(sprite);
	}

	player->setTopMoveAnimation(frames);
}

void PlayerHelper::createBottomMoveAnimation(int playerNumber, Player* player)
{
	const int kNumberOfFrames = 2;
	Vector<SpriteFrame*> frames;
	for (int i = 1; i < kNumberOfFrames; i++)
	{
		std::stringstream ss;
		ss << "player" << playerNumber+1 << "_bottomWalk0" << i << ".png";
		auto sprite = player->getSpritecacher()->getSpriteFrameByName(ss.str());
		frames.pushBack(sprite);
	}

	player->setBottomMoveAnimation(frames);
}
