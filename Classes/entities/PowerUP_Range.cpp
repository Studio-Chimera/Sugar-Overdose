#include "PowerUP_Range.h"
#include "utils/Definitions.h"

PowerUP_Range::PowerUP_Range(Vec2 position, Vec2 customTiledPosition, int axis, int value) {
	this->setCustomTiledPosition(customTiledPosition);
	this->setValue(value);
	this->setAxis(axis);
	this->setPosX(position.x);
	this->setPosY(position.y);

	_spriteCacher = SpriteFrameCache::getInstance();

	std::stringstream plistFile;
	plistFile << "sprites/power-up/powerUp.plist";
	_spriteCacher->addSpriteFramesWithFile(plistFile.str());

	std::stringstream standPng;
	if (axis == AXIS_X) {
		standPng << "powerUp_RangeX.png";
	}
	else if (axis == AXIS_Y) {
		standPng << "powerUp_RangeY.png";
	}

	this->_sprite = new Sprite;
	auto myfile = standPng.str();
	_sprite->initWithSpriteFrameName(myfile);
	getSprite()->setPosition(getPosition());
}

void PowerUP_Range::setCustomTiledPosition(Vec2 customTiledPosition) {
	_customTiledPosX = customTiledPosition.x;
	_customTiledPosY = customTiledPosition.y;
}

int PowerUP_Range::getValue() {
	return _value;
}

void PowerUP_Range::setValue(int value) {
	_value = value;
}

int PowerUP_Range::getAxis() {
	return _axis;
}

void PowerUP_Range::setAxis(int axis) {
	_axis = axis;
}

Sprite* PowerUP_Range::getSprite()
{
	return _sprite;
}

void PowerUP_Range::setPosX(int newPos)
{
	_posX = newPos;
}

void PowerUP_Range::setPosY(int newPos)
{
	_posY = newPos;
}

Vec2 PowerUP_Range::getPosition()
{
	return Vec2(_posX, _posY);
}