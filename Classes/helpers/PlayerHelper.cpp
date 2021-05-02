#include "PlayerHelper.h"
#include <entities/Level.h>

USING_NS_CC;
// ###################################################
// Declarations
// ###################################################

PlayerHelper::PlayerHelper()
{
    _playersInstances = {};
}

PlayerHelper::~PlayerHelper()
{
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

// call this one to have your new player instance
Player* PlayerHelper::createPlayer(Vec2* position, int type, Level* level)
{
	//create player instance
    auto player = new Player;
	player->setPosition(*position);
	//player->setLevel(level);
	setPlayerSprites(player);

	// add players special features
	player->getSprite();

    auto controllerHelper = new ControllerHelper;
	controllerHelper->addControls(player, type); //to use controls on scene add: this->_eventDispatcher->addEventListenerWithSceneGraphPriority(player->getController(), player->getSprite());

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
	std::stringstream standPng;
	standPng << "player" << playerNumber + 1 << "_stand.png";

	// set all sprites
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
		ss << "player"<< playerNumber+1 <<"_sideWalk0" << i << ".png";
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
		ss << "player" << playerNumber+1 << "_topWalk0" << i << ".png";
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