#include "stdafx.h"
#include "Level.h"
#include <iostream>

uint16_t serializer = 0;

//the level object for the game, note that the game assumes that no level will render into negative coordinates
//NB: sizeX and sizeY are in screenwidths(remember that this is actually 1920x1152)

Level::Level(int sizeX, int sizeY, std::vector<Entity*> &entities)
{
	Level::entities = entities;
	Level::Level(sizeX, sizeY, "");
}

Level::Level(int sizeX, int sizeY, std::string tilemapName) {
	id = ++serializer;
	Level::sizeX = sizeX*1920;
	Level::sizeY = sizeY*1152;

	tileMap = new TileMap((float)Level::sizeX, (float)Level::sizeY, tilemapName);
}

Level::~Level()
{

}

void Level::populate(std::vector<Entity*> &entities) {
	Level::entities = entities;
	for (auto e : entities) {

	}
}

void Level::spawnEntities(Entity* spawned) {
	Level::entities.push_back(spawned);
}

void Level::addDrawable(sf::Drawable* target) {
	Level::drawables.push_back(target);
}

void Level::onUpdate(float deltaTime) {

	//int currentsize = entities.size();

	//for (auto e : Level::entities) {
	//	e->onUpdate(deltaTime);
	//}

	for (int i = 0; i < entities.size(); i++) {
		entities[i]->onUpdate(deltaTime);
	}

	for (int i = 0; i < entities.size() - 1; i++) {
		for (int j = i + 1; j < entities.size(); j++) {
			if (entities[i]->AABB->intersects(*entities[j]->AABB)) {
				entities[i]->onCollision(entities[j]);
				entities[j]->onCollision(entities[i]);
			}
		}
	}

}

void Level::removeEntity(Entity* removed) {
	entities.erase(std::remove(entities.begin(), entities.end(), removed), entities.end());
	std::cout << "AAA" << std::endl;
}

void Level::removeDrawable(sf::Drawable* drawable) {
	drawables.erase(std::remove(drawables.begin(), drawables.end(), drawable), drawables.end());
}

void Level::draw(sf::RenderWindow* window, double interpol, sf::FloatRect* renderArea) {

	//tileMap->draw(window, interpol, renderArea);
	window->draw(*tileMap);
	for (auto drawable : Level::drawables) {
		window->draw(*drawable);
	}

	//for (auto e : Level::entities) {
	//	if (!renderArea->intersects(*e->AABB)) continue;
	//	e->draw(window, interpol);
	//}
}


