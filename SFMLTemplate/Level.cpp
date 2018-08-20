#include "stdafx.h"
#include "Level.h"
#include <iostream>

uint16_t serializer = 0;

//the level object for the game, note that the game assumes that no level will render into negative coordinates

Level::Level(int sizeX, int sizeY, std::vector<Entity*> &entities)
{
	Level::entities = entities;
	Level::Level(sizeX, sizeY, "");
}

Level::Level(int sizeX, int sizeY, std::string tilemapName) {
	id = ++serializer;
	Level::sizeX = sizeX*1920;
	Level::sizeY = sizeY*1920;

	tileMap = new TileMap((float)Level::sizeX, (float)Level::sizeY, tilemapName);

	tiles = new std::vector<Tile*>(tileMap->sizeX*tileMap->sizeY);
	load(tilemapName);
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

	for (unsigned int i = 0; i < entities.size(); i++) {
		entities[i]->onUpdate(deltaTime);
	}

	for (unsigned int i = 0; i < entities.size() - 1; i++) {
		for (unsigned int j = i + 1; j < entities.size(); j++) {
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


void Level::load(std::string name) {

	tileMap->tileset.loadFromFile(GetCurrentWorkingDir() + "\\resources\\GrassTileset.png");
	tileMap->tileset.setSmooth(false);

	tileMap->vertBuff->create(tileMap->sizeX*tileMap->sizeY * 4);

	sf::Image image;

	image.loadFromFile(GetCurrentWorkingDir() + "\\resources\\" + name + ".png");

	sf::Vector2u size = image.getSize();
	int height = size.y;
	int width = size.x;

	for (int i = 0; i < width; ++i)
		for (int j = 0; j < height; ++j)
		{

			sf::Color id = image.getPixel(i, j);

			// get the current tile number

			int tileNumber = (id.toInteger() >> (8 * 3)) & 0xff; //gets the 4th byte of the number (which is the 'red' value in an argb system)
			if (tileNumber >= 1) {
				setTile(new Tile(i*(float)TILE_SIZE, (float)j*TILE_SIZE, tileNumber));
			}

			//int tileNumber = tileIDS[i + j * width];

			// find its position in the tileset texture
			int tu = (int)ceil(tileNumber % (tileMap->tileset.getSize().x / TILE_SIZE));
			int tv = (int)ceil(tileNumber / (tileMap->tileset.getSize().x / TILE_SIZE));

			// get a pointer to the current tile's quad
			sf::Vertex* quad = &tileMap->vArr[(i + j * width) * 4];

			// define its 4 corners
			quad[0].position = sf::Vector2f((float)ceil(i * TILE_SIZE) - 1, (float)ceil(j * TILE_SIZE));
			quad[1].position = sf::Vector2f((float)ceil((i + 1) * TILE_SIZE) + 1, (float)ceil(j * TILE_SIZE));
			quad[2].position = sf::Vector2f((float)ceil((i + 1) * TILE_SIZE) + 1, (float)ceil((j + 1) * TILE_SIZE));
			quad[3].position = sf::Vector2f((float)ceil(i * TILE_SIZE) - 1, (float)ceil((j + 1) * TILE_SIZE));

			// define its 4 texture coordinates
			quad[0].texCoords = sf::Vector2f((float)ceil(tu * TILE_SIZE), (float)ceil(tv * TILE_SIZE));
			quad[1].texCoords = sf::Vector2f((float)ceil((tu + 1) * TILE_SIZE), (float)ceil(tv * TILE_SIZE));
			quad[2].texCoords = sf::Vector2f((float)ceil((tu + 1) * TILE_SIZE), (float)ceil((tv + 1) * TILE_SIZE));
			quad[3].texCoords = sf::Vector2f((float)ceil(tu * TILE_SIZE), (float)ceil((tv + 1) * TILE_SIZE));
		}

	tileMap->vertBuff->update(tileMap->vArr);
}

void Level::setTile(Tile* tile) {
	tiles->at(toTiles(tile->posX) + toTiles(tile->posY) * tileMap->sizeX) = tile;
}


