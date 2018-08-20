#include "stdafx.h"
#include "TileMap.h"
#include <unordered_map>

//the map that places and displays tiles in the proper area, this will likely be done through image loading
//NB: the tilemap does NOT work in pixels, it works in its own unit, tiles, which is pixels / TILE_SIZE

//std::unordered_map<int, std::string> tilePool;

TileMap::TileMap(const float levelWidth, const float levelHeight, std::string name)
{
	sizeX = toTiles(levelWidth);
	sizeY = toTiles(levelHeight);
	vertBuff = new sf::VertexBuffer(sf::Quads, sf::VertexBuffer::Dynamic);
	vArr = new sf::Vertex[sizeX*sizeY * 4];
	for (int i = 0; i < sizeX*sizeY * 4; i++) {
		vArr[i] = sf::Vertex();
	}
}


TileMap::~TileMap()
{

}

//Tile* TileMap::getTile(int x, int y) { //x and y are IN TILES | NB: this WILL return null if the tile is not within range
//	if (x < 0 || x >= sizeX || y < 0 || y >= sizeY) {
//		return NULL;
//	} else {
//		return tiles->at(x + y * sizeX);
//	}
//}

//void TileMap::setTile(Tile* tile) {
//	tiles->at(toTiles(tile->posX) + toTiles(tile->posY) * sizeX) = tile;
//}




int toTiles(float pixelIn) { //converts to tilemap unit
	return (int)(pixelIn / TILE_SIZE);
}

float toPixels(int tileIn) { //converts from tilemap unit
	return (float)(tileIn * TILE_SIZE);
}

//void registerTileID(int id, std::string tileName) {
//	tilePool.insert(std::make_pair(id, tileName));
//}

//std::string* getNameFromID(int id) {
//	if (tilePool.find(id) != tilePool.end()) {
//		return &tilePool.at(id);
//	} else {
//		return NULL;
//	}
//}

void TileMap::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = &tileset;
	target.draw(*vertBuff, states);
}