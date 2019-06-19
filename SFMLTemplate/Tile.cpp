#include "stdafx.h"
#include "Tile.h"
#include <iostream>
#include <Windows.h>
#include <string>

std::unordered_map<std::string, sf::Texture*> texturePool;
uint16_t TILE_SIZE = 128;

Tile::Tile(sf::Vector2f position, unsigned int id) : RigidBody(position, Vector2f(128, 128), 0.0f, 0.0f, 0.2f, 0.9f) {
	Tile::position = position;
	Tile::id = id;
}


Tile::~Tile() {

}
