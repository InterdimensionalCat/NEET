#include "stdafx.h"
#include "Mob.h"
#include "Game.h"
#include "GameState.h"

//a MOB (Mobile Entity) is an Entity with movement capabilities, it is assumed that a mob is not controllable by the player, nor is it an NPC
//Living MOB's should be instantiated as the type EntityLivingBase

Mob::Mob(float posX, float posY, float sizeX, float sizeY, Animation* defaultAnimation) : Entity(posX, posY, sizeX, sizeY, defaultAnimation)
{
	motion = new sf::Vector2f(0, 0);
	isAerial = true;
}


Mob::~Mob()
{

}

void Mob::onUpdate(float deltaTime) {
	move();
	Entity::onUpdate(deltaTime);
}

void Mob::move() { //moves the MOB



	//floor collisions
	if (motion->y > 0||!isAerial) {
		bool falling = true;

		for (auto t : *getGame()->CurrentLevel->tileMap->tiles) {
			if (t == NULL) continue;
			if (abs(pos->x - t->posX) > 256 || abs(pos->y - t->posY) > 256) continue;
			if (t->AABB->contains(pos->x + AABB->width / 2 - 24, pos->y + AABB->height)) {
				falling = false;
				motion->y = 0;
				pos->y = t->posY - AABB->height;
			}
		}

		if (falling) {
			for (auto t : *getGame()->CurrentLevel->tileMap->tiles) {
				if (t == NULL) continue;
				if (abs(pos->x - t->posX) > 256 || abs(pos->y - t->posY) > 256) continue;
				if (t->AABB->contains(pos->x + AABB->width / 2 + 24, pos->y + AABB->height)) {
					falling = false;
					motion->y = 0;
					pos->y = t->posY - AABB->height;
				}
			}
		}

		isAerial = falling;

	}

	//wall collisions

	if (motion->x > 0) {

		for (auto t : *getGame()->CurrentLevel->tileMap->tiles) {
			if (t == NULL) continue;
			if (abs(pos->x - t->posX) > 256 || abs(pos->y - t->posY) > 256) continue;
			if (t->AABB->contains(pos->x + AABB->width, pos->y + AABB->height - 50)) {
				motion->x = 0;
				pos->x = t->posX - AABB->width;
				break;
			}

			if (t->AABB->contains(pos->x + AABB->width, pos->y + 50)) {
				motion->x = 0;
				pos->x = t->posX - AABB->width;
				break;
			}
		}

	} else {
		for (auto t : *getGame()->CurrentLevel->tileMap->tiles) {
			if (t == NULL) continue;
			if (abs(pos->x - t->posX) > 256 || abs(pos->y - t->posY) > 256) continue;

			if (t->AABB->contains(pos->x, pos->y + AABB->height - 50)) {
				motion->x = 0;
				pos->x = t->posX + t->AABB->width;
				break;
			}

			if (t->AABB->contains(pos->x, pos->y + 50)) {
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
			if (t->AABB->contains(pos->x + AABB->width / 2, pos->y)) {
				motion->y = 0;
				pos->y = t->posY + t->AABB->height;
			}
		}
	}

	if (pos->x < 0) {
		pos->x = 0;

		currentAnimation->currentFrame->setPosition(*pos);

		motion->x = 0;
	}

	if (pos->x + AABB->width > getGame()->CurrentLevel->sizeX) {
		pos->x = getGame()->CurrentLevel->sizeX - AABB->width;

		currentAnimation->currentFrame->setPosition(*pos);

		motion->x = 0;
	}

	if (pos->y < 0) {
		pos->y = 0;

		currentAnimation->currentFrame->setPosition(*pos);

		motion->y = 0;
	}

	if (pos->y + AABB->height > getGame()->CurrentLevel->sizeY) {
		pos->y = getGame()->CurrentLevel->sizeY - AABB->height;

		currentAnimation->currentFrame->setPosition(*pos);

		motion->y = 0;
		isAerial = false;
	}

	pos->x += motion->x;
	pos->y += motion->y;
	AABB->left = pos->x;
	AABB->top = pos->y;


}

void Mob::draw(sf::RenderWindow* window, double interpol) {
	currentAnimation->currentFrame->setPosition(pos->x, pos->y); //ensures that the sprite is always where the player is
	Entity::draw(window, interpol);
}

bool Mob::onVerticalCollision(sf::FloatRect intersectRect, Tile* tileIn) {
	return 0; //this is so bad
}

bool Mob::onHorizontalCollision(sf::FloatRect intersectRect, Tile* tileIn) {
	return 0; //this is so bad
}
