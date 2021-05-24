#include "Player.h"
#include <iomanip>
#include "Bomb.h"
#include <utils/Definitions.h>

// ###################################################
// Declarations
// ###################################################

Player::Player()
{
	// cache all .plist frames in cacher
	_spriteCacher = SpriteFrameCache::getInstance();

	//init sprite with a standing frame
	_sprite = new Sprite;

	_sideMoveAnimation = new Animation;
	_topMoveAnimation = new Animation;
	_bottomMoveAnimation = new Animation;
}

Player::~Player(){}


// ###################################################
// Getters
// ###################################################

Sprite* Player::getSprite()
{
	return _sprite;
}

SpriteFrameCache* Player::getSpritecacher()
{
	return _spriteCacher;
}

int Player::getPosX()
{
	return _posX;
}

int Player::getPosY()
{
	return _posY;
}

Vec2 Player::getPosition()
{
	return Vec2(_posX, _posY);
}

std::variant<EventListenerCustom*, EventListenerKeyboard*> Player::getController()
{
	return _controller;
}

// ###################################################
// Setters
// ###################################################

void Player::setController(std::variant<EventListenerCustom*, EventListenerKeyboard*> controller)
{
	_controller = controller;
}

void Player::setPosX(int newPos)
{
	_posX = newPos;
}

void Player::setPosY(int newPos)
{
	_posY = newPos;
}

void Player::setPosition(Vec2 position)
{
	_posX = position.x;
	_posY = position.y;
}

void Player::setSideMoveAnimation(Vector<SpriteFrame*> frames)
{
	// create the animation
	const float delay = TIME_WALK_ANIMATION;
	const unsigned int loop = 1;
	_sideMoveAnimation->initWithSpriteFrames(frames, delay, loop);
}

void Player::setTopMoveAnimation(Vector<SpriteFrame*> frames)
{
	// create the animation
	const float delay = TIME_WALK_ANIMATION;
	const unsigned int loop = 1;
	_topMoveAnimation->initWithSpriteFrames(frames, delay, loop);
}

void Player::setBottomMoveAnimation(Vector<SpriteFrame*> frames)
{
	// create the animation
	const float delay = TIME_WALK_ANIMATION;
	const unsigned int loop = 1;
	_bottomMoveAnimation->initWithSpriteFrames(frames, delay, loop);
}

// ###################################################
// Methods
// ###################################################

void Player::moveLeft() {

	bool blocked = blockPlayerIfWalls(DIRECTION_LEFT);
	_sprite->setFlipX(true);
	if (!blocked) {
		_posX -= STEP_PLAYER;
		auto movement = MoveTo::create(TIME_WALK_ANIMATION, getPosition());
		_sprite->runAction(Spawn::create(Animate::create(_sideMoveAnimation), movement, nullptr));
		return;
	}
	_posX -= STEP_PLAYER;
}

void Player::moveRight() {

	bool blocked = blockPlayerIfWalls(DIRECTION_RIGHT);
	_sprite->setFlipX(false);
	if (!blocked) {
		_posX += STEP_PLAYER;
		auto movement = MoveTo::create(TIME_WALK_ANIMATION, getPosition());
		_sprite->runAction(Spawn::create(Animate::create(_sideMoveAnimation), movement, nullptr));
		return;
	}
	_posX += STEP_PLAYER;
}

void Player::moveUp() {

	bool blocked = blockPlayerIfWalls(DIRECTION_TOP);
	if (!blocked) {
		_posY += STEP_PLAYER;
		auto movement = MoveTo::create(TIME_WALK_ANIMATION, getPosition());
		_sprite->runAction(Spawn::create(Animate::create(_topMoveAnimation), movement, nullptr));
		return;
	}
	_posY += STEP_PLAYER;

}

void Player::moveDown() {

	bool blocked = blockPlayerIfWalls(DIRECTION_BOTTOM);
	if (!blocked) {
		_posY -= STEP_PLAYER;
		auto movement = MoveTo::create(TIME_WALK_ANIMATION, getPosition());
		_sprite->runAction(Spawn::create(Animate::create(_bottomMoveAnimation), movement, nullptr));
		return;
	}
	_posY -= STEP_PLAYER;
}

void Player::plantBomb() {
	auto bomb = new Bomb();
	bomb->getSprite()->setPosition(getPosition());  
	Level::getInstance()->addChild(bomb->getSprite());
}

bool Player::blockPlayerIfWalls(const int direction) {

	Vec2 nextPosition = getNextPosition(direction);
	bool collision = Level::getInstance()->checkIfCollision(nextPosition, direction);

	if (collision) {

		return blockPlayer(direction);
	}
	return false;
}

/*
	block player by replacing according to direction
*/
bool Player::blockPlayer(const int direction) {
	const Vec2 pos = getPosition();
	switch (direction)
	{
	case DIRECTION_LEFT:
		this->setPosition(Vec2(pos.x + STEP_PLAYER, pos.y));
		this->orthPosX += 1;
		return true;

	case DIRECTION_RIGHT:
		this->setPosition(Vec2(pos.x - STEP_PLAYER, pos.y));
		this->orthPosX -= 1;
		return true;

	case DIRECTION_TOP:
		this->setPosition(Vec2(pos.x, pos.y - STEP_PLAYER));
		this->orthPosY += 1;
		return true;

	case DIRECTION_BOTTOM:
		this->setPosition(Vec2(pos.x, pos.y + STEP_PLAYER));
		this->orthPosY -= 1;
		return true;
	
	default:
		return false;
	}
	return false;
}

/*
	called when player is moving to calculate where he will be next step
*/
Vec2 Player::getNextPosition(int direction) {
	Vec2 nextPosition = getPosition();
	Vec2 nextTiledPosition;
	switch (direction)
	{
	case DIRECTION_LEFT:
		this->orthPosX -= 1;
		nextTiledPosition.x = this->orthPosX;
		nextTiledPosition.y = this->orthPosY;
		return nextTiledPosition;
	
	case DIRECTION_RIGHT:
		this->orthPosX += 1;
		nextTiledPosition.x = this->orthPosX;
		nextTiledPosition.y = this->orthPosY;
		return nextTiledPosition;
	
	case DIRECTION_TOP:
		this->orthPosY -= 1;
		nextTiledPosition.y = this->orthPosY;
		nextTiledPosition.x = this->orthPosX;
		return nextTiledPosition;
	
	case DIRECTION_BOTTOM:
		this->orthPosY += 1;
		nextTiledPosition.y = this->orthPosY;
		nextTiledPosition.x = this->orthPosX;
		return nextTiledPosition;
	
	default:
		return 0;
	}
}