#include "stdafx.h"
#include "Tile.h"
#include <iostream>
#include <Windows.h>
#include <string>

std::unordered_map<std::string, sf::Texture*> texturePool;
uint16_t TILE_SIZE = 128;

Tile::Tile(float posX, float posY, std::string textureName) {
	Tile::posX = posX;
	Tile::posY = posY;
	Tile::AABB = new sf::FloatRect(posX, posY, TILE_SIZE, TILE_SIZE);

}


Tile::~Tile() {

}

bool Tile::collisionWithEntityVertical(Entity* eIn) {

	sf::FloatRect intersectRect;
	if (AABB->intersects(*eIn->AABB, intersectRect)) {
		if (intersectRect.height <= intersectRect.width) {
			eIn->onVerticalCollision(intersectRect, this);
			return true;
		}
	}

	return false;
}

bool Tile::collisionWithEntityHorizontal(Entity* eIn) {

	sf::FloatRect intersectRect;
	if (AABB->intersects(*eIn->AABB, intersectRect)) {
		if (intersectRect.height > intersectRect.width) {
			eIn->onHorizontalCollision(intersectRect, this);
			return true;
		}
	}
	return false;
}


sf::FloatRect* Tile::entityCollision(Entity* eIn) {
	sf::FloatRect intersectRect;
	if (AABB->intersects(*eIn->AABB, intersectRect)) return &intersectRect;
	return NULL;
}

sf::FloatRect Tile::getAABB() {
	//return sprite.getGlobalBounds();
	return sf::FloatRect(posX, posY, TILE_SIZE, TILE_SIZE);
}

