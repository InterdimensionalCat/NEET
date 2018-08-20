#pragma once
#include "Tile.h"
#include <vector>

class Tile;

int toTiles(float pixelIn);
float toPixels(int tileIn);
//void registerTileID(int id, std::string tileName);
std::string* getNameFromID(int id);

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
	TileMap(const float levelWidth, const float levelHeight, std::string name);
	~TileMap();
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	int sizeX;
	int sizeY;
	sf::VertexBuffer* vertBuff;
	sf::Vertex* vArr;
	sf::Texture tileset;


	//Tile* getTile(int x, int y);
	//void setTile(Tile* tile);
	//void draw(sf::RenderWindow* window, double interpol, sf::FloatRect* renderArea);
	//void load(std::string name);
	//void onUpdate(float deltaTime);
	//std::vector<Tile*>* tiles;
	//sf::VertexArray vertices;
};

