#include "stdafx.h"
#include "TileMap.h"
#include <unordered_map>

//the map that places and displays tiles in the proper area, this will likely be done through image loading
//NB: the tilemap does NOT work in pixels, it works in its own unit, tiles, which is pixels / TILE_SIZE

std::unordered_map<int, std::string> tilePool;

TileMap::TileMap(const float levelWidth, const float levelHeight, std::string name)
{
	sizeX = toTiles(levelWidth);
	sizeY = toTiles(levelHeight);
	tiles = new std::vector<Tile*>(sizeX*sizeY);
	load(name);
}


TileMap::~TileMap()
{

}

Tile* TileMap::getTile(int x, int y) { //x and y are IN TILES | NB: this WILL return null if the tile is not within range
	if (x < 0 || x >= sizeX || y < 0 || y >= sizeY) {
		return NULL;
	} else {
		return tiles->at(x + y * sizeY);
	}
}

void TileMap::setTile(Tile* tile) {
	tiles->at(toTiles(tile->posX) + toTiles(tile->posY) * sizeY) = tile;
	//std::cout << "Tiles loaded" << std::endl;
}

void TileMap::draw(sf::RenderWindow* window, double interpol, sf::FloatRect* renderArea) {
	for (auto t : *tiles) {
		if (t == NULL) continue;
		t->draw(window, interpol);
	}
}

void TileMap::load(std::string name) {
	//TODO: image loading using this method

	//tiles->clear();

	sf::Image image;

	image.loadFromFile(GetCurrentWorkingDir() + "\\resources\\" + name + ".png");

	//const sf::Uint8* arrPixel = image.getPixelsPtr();
	sf::Vector2u size = image.getSize();
	int height = size.y;
	int width = size.x;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			//sf::Uint8 id = arrPixel[x + y * width];
			sf::Color id = image.getPixel(x, y);

			std::string* tileName = getNameFromID(id.toInteger());

			if (tileName != NULL) {
				setTile(new Tile(x*(float)TILE_SIZE, (float)y*TILE_SIZE, *tileName));
			}

			//if (id.toInteger() != 0x54AAF5FF) {
				//setTile(new Tile(x*(float)TILE_SIZE, (float)y*TILE_SIZE, "GrassTile"));
			//}
			//std::cout << id.toInteger() << " " << 0x54AAF5FF << std::endl;
		}
	}

	//setTile(new Tile(TILE_SIZE * 5, TILE_SIZE * 5, "GrassTile"));
	//setTile(new Tile(TILE_SIZE * 5, TILE_SIZE * 4, "GrassTile"));
	//setTile(new Tile(TILE_SIZE * 6, TILE_SIZE * 5, "GrassTile"));
	//setTile(new Tile(TILE_SIZE * 7, TILE_SIZE * 5, "GrassTile"));
	//setTile(new Tile(TILE_SIZE * 8, TILE_SIZE * 5, "GrassTile"));
	//setTile(new Tile(TILE_SIZE * 8, TILE_SIZE * 4, "GrassTile"));

	std::cout << "Tiles loaded" << std::endl;
}

void TileMap::onUpdate(float deltaTime) {

}

int toTiles(float pixelIn) { //converts to tilemap unit
	return (int)(pixelIn / TILE_SIZE);
}

float toPixels(int tileIn) { //converts from tilemap unit
	return (float)(tileIn * TILE_SIZE);
}

void registerTileID(int id, std::string tileName) {
	tilePool.insert(std::make_pair(id, tileName));
}

std::string* getNameFromID(int id) {
	if (tilePool.find(id) != tilePool.end()) {
		return &tilePool.at(id);
	} else {
		return NULL;
	}
}