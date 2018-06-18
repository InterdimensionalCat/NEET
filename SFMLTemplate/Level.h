#pragma once
#include <vector>
#include "Entity.h"
#include "State.h"
#include "player.h"
#include "TileMap.h"

class TileMap;

class Level
{
public:
	Level(long sizeX, long sizeY, std::vector<Entity*> &entities);
	Level(long sizeX, long sizeY, std::string tilemapName);
	~Level();
	uint16_t id;
	std::vector<Entity*> entities;
	long sizeX;
	long sizeY;
	void populate(std::vector<Entity*> &entities);
	void spawnEntities(Entity* spawned);
	void onUpdate(float deltaTime);
	void draw(sf::RenderWindow* window, double interpol, sf::FloatRect* renderArea);
	Player* player;

	TileMap* tileMap;

	sf::Texture bgtexture;
	sf::Sprite bgsprite;
};