#include "stdafx.h"
#include "Level.h"
#include <iostream>
#include "TestEnemy.h"

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

	engine = new PhysicsEngine();
}

Level::~Level()
{

}

void Level::populate(std::vector<Entity*> &entities) {
	Level::entities = entities;

	TestEnemy* test = new TestEnemy(Vector2f(300, 1000));

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

	updatePartitions();

	//for (unsigned int i = 0; i < entities.size() - 1; i++) {
	//	for (unsigned int j = i + 1; j < entities.size(); j++) {
	//		if (entities[i]->AABB->intersects(*entities[j]->AABB)) {
	//			entities[i]->onCollision(entities[j]);
	//			entities[j]->onCollision(entities[i]);
	//		}
	//	}
	//}

	Int64 before = getTimer()->getElapsedTime().asMicroseconds();

	engine->updatePhysics(deltaTime, partitions, &entities, tiles);
	//engine->onUpdate(deltaTime, partitions, &entities, tiles);
	//engine->onUpdate(deltaTime, partitions);

	Int64 after = getTimer()->getElapsedTime().asMicroseconds();

	if (Keyboard::isKeyPressed(Keyboard::Num8)) {
		std::cout << "PhysicsTime: " << after - before << std::endl;
	}
}

void Level::updatePartitions() {
	for (int i = 0; i < partitions->size(); i++) {
		for (int j = 0; j < partitions->at(i)->size(); j++) {
			partitions->at(i)->at(j)->entities->clear();
		}
	}

	for (auto e : entities) {
		Vector2f epos1 = e->origin - e->dimensions / 2.0f;
		Vector2f epos2 = e->origin + e->dimensions / 2.0f;
		Vector2f epos3 = e->origin - Vector2f(e->dimensions.x, -e->dimensions.y) / 2.0f;
		Vector2f epos4 = e->origin + Vector2f(e->dimensions.x, -e->dimensions.y) / 2.0f;
		int i = (int)epos1.x / (128 * partitionSize);
		int j = (int)epos1.y / (128 * partitionSize);
		int i1 = (int)epos2.x / (128 * partitionSize);
		int j1 = (int)epos2.y / (128 * partitionSize);
		int i2 = (int)epos3.x / (128 * partitionSize);
		int j2 = (int)epos3.y / (128 * partitionSize);
		int i3 = (int)epos4.x / (128 * partitionSize);
		int j3 = (int)epos4.y / (128 * partitionSize);
		//std::cout << i << " " << j << std::endl;
		try {
			partitions->at(i)->at(j)->addEntity(e);
			partitions->at(i1)->at(j1)->addEntity(e);
			partitions->at(i2)->at(j2)->addEntity(e);
			partitions->at(i3)->at(j3)->addEntity(e);
		}
		catch(std::out_of_range exc) {
			e->setDead();
		}

		epos1 = e->origin + e->velocity - e->dimensions / 2.0f;
		epos2 = e->origin + e->velocity + e->dimensions / 2.0f;
		epos3 = e->origin + e->velocity - Vector2f(e->dimensions.x, -e->dimensions.y) / 2.0f;
		epos4 = e->origin + e->velocity + Vector2f(e->dimensions.x, -e->dimensions.y) / 2.0f;
		i = (int)epos1.x / (128 * partitionSize);
		j = (int)epos1.y / (128 * partitionSize);
		i1 = (int)epos2.x / (128 * partitionSize);
		j1 = (int)epos2.y / (128 * partitionSize);
		i2 = (int)epos3.x / (128 * partitionSize);
		j2 = (int)epos3.y / (128 * partitionSize);
		i3 = (int)epos4.x / (128 * partitionSize);
		j3 = (int)epos4.y / (128 * partitionSize);

		try {
			partitions->at(i)->at(j)->addEntity(e);
			partitions->at(i1)->at(j1)->addEntity(e);
			partitions->at(i2)->at(j2)->addEntity(e);
			partitions->at(i3)->at(j3)->addEntity(e);
		}
		catch (std::out_of_range exc) {
			e->setDead();
		}



		//if (i1 != i || j1 != j) {
		//	//std::cout << "As Well As " << i1 << " " << j1 << std::endl;
		//}
	}

	//std::cout << "AAA" << std::endl;

}

void Level::removeEntity(Entity* removed) {
	entities.erase(std::remove(entities.begin(), entities.end(), removed), entities.end());
	//std::cout << "AAA" << std::endl;
}

void Level::removeDrawable(sf::Drawable* drawable) {
	drawables.erase(std::remove(drawables.begin(), drawables.end(), drawable), drawables.end());
}

void Level::draw(sf::RenderWindow* window, double interpol, sf::FloatRect* renderArea) {


	//std::cout << entities.size() << std::endl;

	//tileMap->draw(window, interpol, renderArea);
	window->draw(*tileMap);
	for (auto drawable : Level::drawables) {
		window->draw(*drawable);
	}

	if (debug) {
		for (int i = 0; i < partitions->size(); i++) {
			for (int j = 0; j < partitions->at(0)->size(); j++) {
				Vector2f pos((float)(i * partitionSize * TILE_SIZE), (float)(j * partitionSize * TILE_SIZE));
				if (!renderArea->contains(pos)) continue;
				RectangleShape drawn(Vector2f((float)(partitionSize*TILE_SIZE), (float)(partitionSize * TILE_SIZE)));
				drawn.setFillColor(Color(0, 0, 0, 0));
				drawn.setOutlineColor(Color(255, 0, 0, 255));
				drawn.setOutlineThickness(2);
				drawn.move(pos);
				window->draw(drawn);
			}
		}

		for (auto t : *tiles) {
			if (t == NULL) continue;
			for (auto vec : t->correctNormals) {
				RectangleShape drawn(25.0f*(vec)+Vector2f(5, 5));
				drawn.setFillColor(Color(0, 0, 0, 0));
				drawn.setOutlineColor(Color(255, 0, 0, 255));
				drawn.setOutlineThickness(2);
				drawn.move(t->origin);
				window->draw(drawn);
			}
		}


	}

	//for (auto e : Level::entities) {
	//	if (!renderArea->intersects(*e->AABB)) continue;
	//	e->draw(window, interpol);
	//}
}


void Level::load(std::string name) {


	partitions = new std::vector<std::vector<SpacialPartition*>*>();

	tileKey = new vector<vector<int>>(tileMap->sizeX);
	for (int i = 0; i < tileKey->size(); i++) {
		tileKey->at(i) = vector<int>(tileMap->sizeY);
	}

	partitions->resize(Level::sizeX / (128 * partitionSize));
	for (int i = 0; i < partitions->size(); i++) {
		partitions->at(i) = new std::vector<SpacialPartition*>();
		partitions->at(i)->resize(Level::sizeY / (128 * partitionSize));
		for (int j = 0; j < partitions->at(i)->size(); j++) {
			partitions->at(i)->at(j) = new SpacialPartition();
		}
	}

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

			unsigned int tileNumber = (id.toInteger() >> (8 * 3)) & 0xff; //gets the 4th byte of the number (which is the 'red' value in an argb system)

			tileKey->at(i).at(j) = tileNumber;

			if (tileNumber >= 1) {
				setTile(new Tile(sf::Vector2f(i*(float)TILE_SIZE, (float)j*TILE_SIZE), tileNumber));
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
			quad[0].texCoords = sf::Vector2f((float)ceil(tu * TILE_SIZE) + 1, (float)ceil(tv * TILE_SIZE));
			quad[1].texCoords = sf::Vector2f((float)ceil((tu + 1) * TILE_SIZE), (float)ceil(tv * TILE_SIZE));
			quad[2].texCoords = sf::Vector2f((float)ceil((tu + 1) * TILE_SIZE), (float)ceil((tv + 1) * TILE_SIZE));
			quad[3].texCoords = sf::Vector2f((float)ceil(tu * TILE_SIZE) + 1, (float)ceil((tv + 1) * TILE_SIZE));
		}

	tileMap->vertBuff->update(tileMap->vArr);


	for (int i = 0; i < partitions->size(); i++) {
		for (int j = 0; j < partitions->at(0)->size(); j++) {
			for (int k = 0; k < partitionSize; k++) {
				for (int l = 0; l < partitionSize; l++) {
					partitions->at(i)->at(j)->tiles[k][l] = tiles->at((i*partitionSize + k) + (j*partitionSize + l) * tileMap->sizeX);
				}
			}
		}
	}

	std::cout << "AAA" << std::endl;



	//for (int i = 0; i < tiles->size(); i++) {

	//	if (tiles->at(i) == NULL) {
	//		tiles->erase(tiles->begin() + i);
	//		i--;
	//	}


	//}

	for (int i = 0; i < tiles->size(); i++) {
		if (tiles->at(i) == NULL) continue;
		correctNormals(tiles->at(i));
	}

}

void Level::setTile(Tile* tile) {
	tiles->at(toTiles(tile->position.x) + toTiles(tile->position.y) * tileMap->sizeX) = tile;
}

Tile* Level::getTile(int x, int y) { //x and y are IN TILES | NB: this WILL return null if the tile is not within range
	if (x < 0 || x >= toTiles((float)sizeX) || y < 0 || y >= toTiles((float)sizeY)) {
		return NULL;
	}
	else {
		return tiles->at(x + y * toTiles((float)sizeX));
	}
}

Vector2i getKey(Vector2f position) {
	return Vector2i((int)position.x / TILE_SIZE, (int)position.y / TILE_SIZE);
}

bool Level::isKeyOccupied(Vector2i keyPos) {
	return tileKey->at(keyPos.x).at(keyPos.y) > 0;
}

void Level::correctNormals(Tile* tile) {
	for (int i = 0; i < tile->correctNormals.size(); i++) {
		Vector2f vec = tile->correctNormals.at(i);
		Vector2i key = getKey(tile->origin) + (Vector2i)vec;
		if (key.x < 0 || key.y < 0 || key.x >= tileKey->size() || key.y >= tileKey->at(0).size()) continue;
		if (isKeyOccupied(key)) {
			tile->correctNormals.erase(std::remove(tile->correctNormals.begin(), tile->correctNormals.end(), vec), tile->correctNormals.end());
			i--;

			cout << "removed vec" << vec.x << " " << vec.y << endl;

		}
	}
}


