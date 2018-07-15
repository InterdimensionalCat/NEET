#pragma once

#include <SFML\Graphics.hpp>
#include <unordered_map>
#include "Entity.h"

class Entity;

extern uint16_t TILE_SIZE;

class Tile
{
public:
	Tile(float posX, float posY, std::string textureName);
	~Tile();
	sf::FloatRect* AABB;
	float posX;
	float posY;
	sf::Texture texture;
	sf::Sprite sprite;
	bool collisionWithEntityVertical(Entity* eIn);
	bool collisionWithEntityHorizontal(Entity* eIn);
	sf::FloatRect* entityCollision(Entity* eIn);
	sf::FloatRect getAABB();
};

