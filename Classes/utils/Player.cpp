#include "Player.h"
#include <iomanip>

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
	auto physicsBody = PhysicsBody::createBox(Size(65.0f, 65.0f),
		PhysicsMaterial(0.1f, 1.0f, 0.0f));
	physicsBody->setDynamic(false); // set to true for gravity

	//apply physicsBody to the sprite
	_sprite->addComponent(physicsBody);
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

void Player::setPosition(Vec2* position)
{
	_posX = position->x;
	_posY = position->y;
}

void Player::setSideMoveAnimation(Vector<SpriteFrame*> frames)
{
	// create the animation
	const float delay = 0.1f;
	const unsigned int loop = 1;
	_sideMoveAnimation->initWithSpriteFrames(frames, delay, loop);
}

void Player::setTopMoveAnimation(Vector<SpriteFrame*> frames)
{
	// create the animation
	const float delay = 0.1f;
	const unsigned int loop = 1;
	_topMoveAnimation->initWithSpriteFrames(frames, delay, loop);
}

void Player::setBottomMoveAnimation(Vector<SpriteFrame*> frames)
{
	// create the animation
	const float delay = 0.1f;
	const unsigned int loop = 1;
	_bottomMoveAnimation->initWithSpriteFrames(frames, delay, loop);
}
// ###################################################
// Methods
// ###################################################

void Player::actualizePosition()
{
	_sprite->setPosition(getPosition());
}

void Player::moveLeft() {
	_sprite->setFlipX(true);
	_posX -= 35;
	auto movement = MoveTo::create(0.6, getPosition());
	_sprite->runAction(Spawn::create(Animate::create(_sideMoveAnimation), movement, nullptr));
}

void Player::moveRight() {
	_sprite->setFlipX(false);
	_posX += 35;
	auto movement = MoveTo::create(0.6, getPosition());
	_sprite->runAction(Spawn::create(Animate::create(_sideMoveAnimation), movement,0.5f, nullptr));
}

void Player::moveTop() {
	_posY += 35;
	auto movement = MoveTo::create(0.6, getPosition());
	_sprite->runAction(Spawn::create(Animate::create(_topMoveAnimation), movement, 0.5f, nullptr));
}

void Player::moveBottom() {
	_posX += 35;
	auto movement = MoveTo::create(0.6, getPosition());
	_sprite->runAction(Spawn::create(Animate::create(_bottomMoveAnimation), movement, 0.5f, nullptr));
}

void Player::plantBomb() {
	//Todo
}
