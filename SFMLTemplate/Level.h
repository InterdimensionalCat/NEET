#pragma once
#include <vector>
#include "Entity.h"
#include "State.h"
#include "player.h"
#include "TileMap.h"

class TileMap;

//wrapper class for "rooms" or levels, level sizes use a special unit known as "screensizes" dispite the name, this dimension is slightly larger than 1 screen, at 1920x1152

class Level
{
public:
	//Level(long sizeX, long sizeY, std::vector<Entity*> &entities);
	//Level(long sizeX, long sizeY, std::string tilemapName);
	Level(int sizeX, int sizeY, std::vector<Entity*> &entities);
	Level(int sizeX, int sizeY, std::string tilemapName);
	~Level();
	uint16_t id;
	std::vector<Entity*> entities;
	std::vector<sf::Drawable*> drawables;
	long sizeX;
	long sizeY;
	void populate(std::vector<Entity*> &entities);
	void spawnEntities(Entity* spawned);
	void addDrawable(sf::Drawable* target);
	void onUpdate(float deltaTime);
	void draw(sf::RenderWindow* window, double interpol, sf::FloatRect* renderArea);
	void removeEntity(Entity* removed);
	void removeDrawable(sf::Drawable* drawable);

	Player* player;
	TileMap* tileMap;

	sf::Texture bgtexture;
	sf::Sprite bgsprite;
};