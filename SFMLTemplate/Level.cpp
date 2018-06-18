#include "stdafx.h"
#include "Level.h"
#include <iostream>

uint16_t serializer = 0;

//the level object for the game, note that the game assumes that no level will render into negative coordinates


Level::Level(long sizeX, long sizeY, std::vector<Entity*> &entities)
{
	Level::entities = entities;
	Level::Level(sizeX, sizeY, "");
}

Level::Level(long sizeX, long sizeY, std::string tilemapName) {
	id = ++serializer;
	Level::sizeX = sizeX;
	Level::sizeY = sizeY;

	tileMap = new TileMap((float)sizeX, (float)sizeY, tilemapName);
}

Level::~Level()
{

}

void Level::populate(std::vector<Entity*> &entities) {
	Level::entities = entities;
}

void Level::spawnEntities(Entity* spawned) {
	Level::entities.push_back(spawned);
}

void Level::onUpdate(float deltaTime) {
	for (auto e : Level::entities) {
		e->onUpdate(deltaTime);
		//testTile->collisionWithEntity(e);

	}

	//testTile->collisionWithEntity(player);
}

void Level::draw(sf::RenderWindow* window, double interpol, sf::FloatRect* renderArea) {
	//window->draw(bg);

	tileMap->draw(window, interpol, renderArea);
	for (auto e : Level::entities) {
		e->draw(window, interpol);
	}
}


