#include "stdafx.h"
#include "Mob.h"
#include "SFMLTemplate.h"
#include "GameState.h"

//a MOB (Mobile Entity) is an Entity with movement capabilities, it is assumed that a mob is not controllable by the player, nor is it an NPC
//Living MOB's should be instantiated as the type EntityLivingBase

Mob::Mob(float posX, float posY, std::string textureName, float sizeX, float sizeY) : Entity(posX, posY, textureName, sizeX, sizeY)
{
	motion = new sf::Vector2f(0, 0);
}


Mob::~Mob()
{

}

void Mob::onUpdate(float deltaTime) {
	move();
	Entity::onUpdate(deltaTime);
}

void Mob::move() { //moves the MOB
	pos->x += motion->x/4;
	pos->y += motion->y/4;

	AABB->left += motion->x/4; //updates the AABB's position
	AABB->top += motion->y/4;

	isAerial = true;

	for (int i = 1; i <= 3; i++) {
		for (auto t : *getGame()->CurrentLevel->tileMap->tiles) {
			if (t == NULL) continue;
			if (t->collisionWithEntityVertical(this)) break;
		}
		pos->y += motion->y / 4;
		AABB->top += motion->y / 4;
	}

	for (int i = 1; i <= 3; i++) {
		for (auto t : *getGame()->CurrentLevel->tileMap->tiles) {
			if (t == NULL) continue;
			if (t->collisionWithEntityHorizontal(this)) break;
		}

		pos->x += motion->x / 4;
		AABB->left += motion->x / 4;
	}

	if (pos->x < 0) {
		pos->x = 0;
		AABB->left = 0;
		motion->x = 0;
	}

	if (pos->x + AABB->width > getGame()->CurrentLevel->sizeX) {
		pos->x = getGame()->CurrentLevel->sizeX - AABB->width;
		AABB->left = getGame()->CurrentLevel->sizeX - AABB->width;
		motion->x = 0;
	}

	if (pos->y < 0) {
		pos->y = 0;
		AABB->top = 0;
		motion->y = 0;
	}

	if (pos->y + AABB->height > getGame()->CurrentLevel->sizeY) {
		pos->y = getGame()->CurrentLevel->sizeY - AABB->height;
		AABB->top = getGame()->CurrentLevel->sizeY - AABB->height;
		motion->y = 0;
	}
}

void Mob::draw(sf::RenderWindow* window, double interpol) {
	sprite.setPosition(pos->x, pos->y); //ensures that the sprite is always where the player is
	Entity::draw(window, interpol);
}

bool Mob::onVerticalCollision(sf::FloatRect intersectRect, Tile* tileIn) {
	return 0; //this is so bad
}

bool Mob::onHorizontalCollision(sf::FloatRect intersectRect, Tile* tileIn) {
	return 0; //this is so bad
}
