#include "Player.h"
#include <iomanip>
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

	// create a physic body
	auto physicsBody = PhysicsBody::createBox(Size(112.5f, 188.5f), PhysicsMaterial(0.1f, 1.0f, 0.0f));
	physicsBody->setDynamic(false);

	/*physicsBody->setRotationEnable(false);
	physicsBody->setGravityEnable(true);*/

	//physicsBody->setCollisionBitmask(2); // Set a tag
	physicsBody->setContactTestBitmask(true); // Allow to collision to be detected

	//apply physicsBody to the sprite
	//_sprite->addComponent(physicsBody);
	_sprite->setPhysicsBody(physicsBody); // on charly tutorial


	_sideMoveAnimation = new Animation;
	_topMoveAnimation = new Animation;
	_bottomMoveAnimation = new Animation;
}

Player::~Player()
{
}

// ###################################################
// Getters
// ###################################################

//Level* Player::getLevel() {
//	return _level;
//};

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

//void Player::setLevel(Level* level) {
//	 _level = level;
//}

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
	//if (!blocked) {
		_sprite->setFlipX(true);
		_posX -= STEP_PLAYER;
		auto movement = MoveTo::create(TIME_WALK_ANIMATION, getPosition());
		_sprite->runAction(Spawn::create(Animate::create(_sideMoveAnimation), movement, nullptr));
	//}
}

void Player::moveRight() {

	bool blocked = blockPlayerIfWalls(DIRECTION_RIGHT);
	//if (!blocked) {
		_sprite->setFlipX(false);
		_posX += STEP_PLAYER;
		auto movement = MoveTo::create(TIME_WALK_ANIMATION, getPosition());
		_sprite->runAction(Spawn::create(Animate::create(_sideMoveAnimation), movement, nullptr));
	//}
}

void Player::moveUp() {
	bool blocked = blockPlayerIfWalls(DIRECTION_TOP);
	//if (!blocked) {
		_posY += STEP_PLAYER;
		auto movement = MoveTo::create(TIME_WALK_ANIMATION, getPosition());
		_sprite->runAction(Spawn::create(Animate::create(_topMoveAnimation), movement, nullptr));
	//}
}

void Player::moveDown() {
	bool blocked = blockPlayerIfWalls(DIRECTION_BOTTOM);
	//if (!blocked) {
		_posY -= STEP_PLAYER;
		auto movement = MoveTo::create(TIME_WALK_ANIMATION, getPosition());
		_sprite->runAction(Spawn::create(Animate::create(_bottomMoveAnimation), movement, nullptr));
	//}	
}

void Player::plantBomb() {
	//Todo
}

void Player::stopAnimation(cocos2d::RepeatForever* ani) {
	CCLOG("STOP ANIMATION");
	_sprite->stopAction(ani);
}

/*
	detect walls, which are destructible and collisionable, 
	and block player if it enter in contact with it
*/
bool Player::blockPlayerIfWalls(const int direction)
{
	const Vec2 pos = this->getPosition();
	Level* currentLevel = Level::getInstance();
	const Sprite* tile = currentLevel->getTileCoordForPosition(pos);
	int id = 0;
	if (tile) {
		SpriteBatchNode* spriteBatchNode = tile->getBatchNode();
		 id = spriteBatchNode->getTag();
		 if (id == 2) { // Tag 2 is walls
			 return blockPlayer(direction);
		 }
	}
}

/*
	block player by replacing according to direction
*/
bool Player::blockPlayer(const int direction) {
	const Vec2 pos = this->getPosition();
	switch (direction)
	{
	case DIRECTION_LEFT:
		this->setPosition(Vec2(pos.x + 25, pos.y));
		return true;
	case DIRECTION_RIGHT:
		this->setPosition(Vec2(pos.x - 25, pos.y));
		return true;
	case DIRECTION_TOP:
		this->setPosition(Vec2(pos.x, pos.y + 25));
		return true;
	case DIRECTION_BOTTOM:
		this->setPosition(Vec2(pos.x, pos.y - 25));
		return true;
	default:
		return false;
	}
}