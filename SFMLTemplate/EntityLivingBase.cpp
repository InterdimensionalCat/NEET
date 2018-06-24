#include "stdafx.h"
#include "EntityLivingBase.h"

//EntityLivingBases are Living mobs, they are assumed to move using an AI or keyboard input, EntityLivingBases are also assumed to have HP and Take damage however the actual Player should be instantiated as type player

EntityLivingBase::EntityLivingBase(float posX, float posY, std::string textureName, float sizeX, float sizeY, int hitpoints) : Mob(posX, posY, textureName, sizeX, sizeY)
{
	EntityLivingBase::hitpoints = hitpoints;
	maxHitPoints = hitpoints;
}


EntityLivingBase::~EntityLivingBase()
{

}

void EntityLivingBase::damage(uint16_t damage) { //damages the EntityLivingBase, note that passing a negative number (ie -1) will be essentially an instant kill due to unsigned integer underflow
	hitpoints -= damage;
	if (hitpoints <= 0) {
		kill();
	}
}

void EntityLivingBase::heal(uint16_t health) { //heals the EntityLivingBase, any number greater than maxHitPoints will heal the EntityLivingBase up to its max hp
	hitpoints += health;
	if (hitpoints > maxHitPoints) {
		hitpoints = maxHitPoints;
	}
}

void EntityLivingBase::kill() { //called when an EntityLivingBase loses all of its health

}

void EntityLivingBase::onUpdate(float deltaTime) {
	Mob::onUpdate(deltaTime);
}

bool EntityLivingBase::onVerticalCollision(sf::FloatRect intersectRect, Tile* tileIn) {
	if (pos->y >= tileIn->posY) {
		if (intersectRect.height <= 1) return false;
		pos->y += intersectRect.height - 1;
		isAerial = true;
	} else {
		if (intersectRect.height <= 1) return false;
		isAerial = false;
		pos->y -= intersectRect.height - 1;
	}

	AABB->top = pos->y;

	motion->y = 0;

	return false;
	}

bool EntityLivingBase::onHorizontalCollision(sf::FloatRect intersectRect, Tile* tileIn) {
	if (pos->x >= tileIn->posX) {
		if (intersectRect.width <= 1) return false;
		if (isAerial) {
			pos->x += intersectRect.width;
		} else {
			pos->x += intersectRect.width - 1;
		}
	} else {
		if (intersectRect.width <= 1) return false;
		if (isAerial) {
			pos->x -= intersectRect.width;
		} else {
			pos->x -= intersectRect.width - 1;
		}
	}

	AABB->left = pos->x;

	motion->x = 0;

	return true;
}

 bool EntityLivingBase::jump(float velocity) {
	 if (isAerial) return false;
	 motion->y = -velocity;
	 isAerial = true;
	 return true;
}
