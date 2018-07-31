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
	vertBuff = new sf::VertexBuffer(sf::Quads, sf::VertexBuffer::Dynamic);
	vArr = new sf::Vertex[sizeX*sizeY * 4];
	for (int i = 0; i < sizeX*sizeY * 4; i++) {
		vArr[i] = sf::Vertex();
	}
	load(name);
}


TileMap::~TileMap()
{

}

Tile* TileMap::getTile(int x, int y) { //x and y are IN TILES | NB: this WILL return null if the tile is not within range
	if (x < 0 || x >= sizeX || y < 0 || y >= sizeY) {
		return NULL;
	} else {
		return tiles->at(x + y * sizeX);
	}
}

void TileMap::setTile(Tile* tile) {
	tiles->at(toTiles(tile->posX) + toTiles(tile->posY) * sizeX) = tile;
}

void TileMap::load(std::string name) {

	tileset.loadFromFile(GetCurrentWorkingDir() + "\\resources\\GrassTileset.png");
	tileset.setSmooth(false);

	vertBuff->create(sizeX*sizeY * 4);

	sf::Image image;

	image.loadFromFile(GetCurrentWorkingDir() + "\\resources\\" + name + ".png");

	sf::Vector2u size = image.getSize();
	int height = size.y;
	int width = size.x;

	std::vector<int> tileIDS(height*width);

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			sf::Color id = image.getPixel(x, y);

			std::string* tileName = getNameFromID(id.toInteger());

			if (tileName != NULL) {
				setTile(new Tile(x*(float)TILE_SIZE, (float)y*TILE_SIZE, *tileName));
				tileIDS.at(x + y * width) = 1;
			} else {
				tileIDS.at(x + y * width) = 0;
			}
		}
	}

	for (int i = 0; i < width; ++i)
		for (int j = 0; j < height; ++j)
		{
			// get the current tile number
			int tileNumber = tileIDS[i + j * width];


			// find its position in the tileset texture
			int tu = ceil(tileNumber % (tileset.getSize().x / TILE_SIZE));
			int tv = ceil(tileNumber / (tileset.getSize().x / TILE_SIZE));

			// get a pointer to the current tile's quad
			sf::Vertex* quad = &vArr[(i + j * width) * 4];

			// define its 4 corners
			quad[0].position = sf::Vector2f(ceil(i * TILE_SIZE) - 1, ceil(j * TILE_SIZE));
			quad[1].position = sf::Vector2f(ceil((i + 1) * TILE_SIZE) + 1, ceil(j * TILE_SIZE));
			quad[2].position = sf::Vector2f(ceil((i + 1) * TILE_SIZE) + 1, ceil((j + 1) * TILE_SIZE));
			quad[3].position = sf::Vector2f(ceil(i * TILE_SIZE) - 1, ceil((j + 1) * TILE_SIZE));

			// define its 4 texture coordinates
			quad[0].texCoords = sf::Vector2f(ceil(tu * TILE_SIZE), ceil(tv * TILE_SIZE));
			quad[1].texCoords = sf::Vector2f(ceil((tu + 1) * TILE_SIZE), ceil(tv * TILE_SIZE));
			quad[2].texCoords = sf::Vector2f(ceil((tu + 1) * TILE_SIZE), ceil((tv + 1) * TILE_SIZE));
			quad[3].texCoords = sf::Vector2f(ceil(tu * TILE_SIZE), ceil((tv + 1) * TILE_SIZE));
		}

	vertBuff->update(vArr);
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
void TileMap::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = &tileset;
	target.draw(*vertBuff, states);
}