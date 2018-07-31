#include "stdafx.h"
#include "EntityLivingBase.h"
#include "GameState.h"

//EntityLivingBases are Living mobs, they are assumed to move using an AI or keyboard input, EntityLivingBases are also assumed to have HP and Take damage however the actual Player should be instantiated as type player

EntityLivingBase::EntityLivingBase(float posX, float posY, float sizeX, float sizeY, int hitpoints/*, Animation* defaultAnimation*/) : Mob(posX, posY, sizeX, sizeY/*, defaultAnimation*/)
{
	EntityLivingBase::hitpoints = hitpoints;
	maxHitPoints = hitpoints;
	isAerial = true;
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

void EntityLivingBase::move() {
	//floor collisions
	if (motion->y > 0 || !isAerial) {
		bool falling = true;

		for (auto t : *getGame()->CurrentLevel->tileMap->tiles) {
			if (t == NULL) continue;
			if (abs(pos->x - t->posX) > 256 || abs(pos->y - t->posY) > 256) continue;
			if (t->AABB->contains(calculatePoints(1))) {
				falling = false;
				motion->y = 0;
				pos->y = t->posY - AABB->height;
			}
		}

		if (falling) {
			for (auto t : *getGame()->CurrentLevel->tileMap->tiles) {
				if (t == NULL) continue;
				if (abs(pos->x - t->posX) > 256 || abs(pos->y - t->posY) > 256) continue;
				if (t->AABB->contains(calculatePoints(2))) {
					falling = false;
					motion->y = 0;
					pos->y = t->posY - AABB->height;
				}
			}
		}

		isAerial = falling;

	}

	//wall collisions

	if (motion->x >= 0) {

		for (auto t : *getGame()->CurrentLevel->tileMap->tiles) {
			if (t == NULL) continue;
			if (abs(pos->x - t->posX) > 256 || abs(pos->y - t->posY) > 256) continue;
			if (t->AABB->contains(calculatePoints(4))) {
				motion->x = 0;
				pos->x = t->posX - AABB->width;
				break;
			}

			if (t->AABB->contains(calculatePoints(6))) {
				motion->x = 0;
				pos->x = t->posX - AABB->width;
				break;
			}
		}

	}

	if (motion->x <= 0) {
		for (auto t : *getGame()->CurrentLevel->tileMap->tiles) {
			if (t == NULL) continue;
			if (abs(pos->x - t->posX) > 256 || abs(pos->y - t->posY) > 256) continue;

			if (t->AABB->contains(calculatePoints(3))) {
				motion->x = 0;
				pos->x = t->posX + t->AABB->width;
				break;
			}

			if (t->AABB->contains(calculatePoints(5))) {
				motion->x = 0;
				pos->x = t->posX + t->AABB->width;
				break;
			}
		}
	}

	//Ceiling Collisions
	if (motion->y < 0) {
		for (auto t : *getGame()->CurrentLevel->tileMap->tiles) {
			if (t == NULL) continue;
			if (abs(pos->x - t->posX) > 256 || abs(pos->y - t->posY) > 256) continue;
			if (t->AABB->contains(calculatePoints(7))) {
				motion->y = 0;
				pos->y = t->posY + t->AABB->height;
			}
		}
	}

	//this check is to ensure that the EntityLivingBase stays within the boundries of the level

	if (pos->x < 0) {
		pos->x = 0;
		motion->x = 0;
	}

	if (pos->x + AABB->width > getGame()->CurrentLevel->sizeX) {
		pos->x = getGame()->CurrentLevel->sizeX - AABB->width;
		motion->x = 0;
	}

	if (pos->y < 0) {
		pos->y = 0;
		motion->y = 0;
	}

	if (pos->y + AABB->height > getGame()->CurrentLevel->sizeY) {
		pos->y = getGame()->CurrentLevel->sizeY - AABB->height;
		motion->y = 0;
		isAerial = false;
	}

	pos->x += motion->x;
	pos->y += motion->y;
	AABB->left = pos->x;
	AABB->top = pos->y;
}

 bool EntityLivingBase::jump(float velocity) {
	 if (isAerial) return false;
	 motion->y = -velocity;
	 isAerial = true;
	 return true;
}

 sf::Vector2f EntityLivingBase::calculatePoints(int id) {
	 switch (id) {
		 sf::Vector2f* vec;
	 case 1: //Left Floor
		 vec = new sf::Vector2f(pos->x + AABB->width / 2 - 24, pos->y + AABB->height);
		 //sf::Transform().translate(vec->x, vec->y).rotate(rotation * 90).transformPoint(*vec);
		 return *vec;
	 case 2: //Right Floor
		 vec = new sf::Vector2f(pos->x + AABB->width / 2 + 24, pos->y + AABB->height);
		 //sf::Transform().translate(vec->x, vec->y).rotate(rotation * 90).transformPoint(*vec);
		 return *vec;
	 case 3: //Lower Left Wall
		 vec = new sf::Vector2f(pos->x, pos->y + AABB->height - 50);
		 //sf::Transform().translate(vec->x, vec->y).rotate(rotation * 90).transformPoint(*vec);
		 return *vec;
	 case 4: // Lower Right Wall
		 vec = new sf::Vector2f(pos->x + AABB->width, pos->y + AABB->height - 50);
		//sf::Transform().translate(vec->x, vec->y).rotate(rotation * 90).transformPoint(*vec);
		 return *vec;
	 case 5: //Upper Left Wall
		 vec = new sf::Vector2f(pos->x, pos->y + 50);
		 //sf::Transform().translate(vec->x, vec->y).rotate(rotation * 90).transformPoint(*vec);
		 return *vec;
	 case 6: //Upper Right Wall
		 vec = new sf::Vector2f(pos->x + AABB->width, pos->y + 50);
		 //sf::Transform().translate(vec->x, vec->y).rotate(rotation * 90).transformPoint(*vec);
		 return *vec;
	 case 7: //Ceiling
		 vec = new sf::Vector2f(pos->x + AABB->width / 2, pos->y);
		// sf::Transform().translate(vec->x, vec->y).rotate(rotation * 90).transformPoint(*vec);
		 return *vec;
	 }
 }
