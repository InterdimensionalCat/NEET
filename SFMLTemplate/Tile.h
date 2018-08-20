#pragma once

#include <SFML\Graphics.hpp>
#include <unordered_map>
#include "Entity.h"

class Entity;

extern uint16_t TILE_SIZE;

class Tile
{
public:
	Tile(float posX, float posY, int id);
	~Tile();
	sf::FloatRect* AABB;
	float posX;
	float posY;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::FloatRect getAABB();
};

