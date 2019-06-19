#pragma once

#include <SFML\Graphics.hpp>
#include <unordered_map>
#include "Entity.h"
#include "RigidBody.h"

class Entity;
class RigidBody;

extern uint16_t TILE_SIZE;

class Tile : public RigidBody
{
public:
	Tile(sf::Vector2f position, unsigned int id);
	~Tile();
	sf::Vector2f position;
	vector<Vector2f> correctNormals = { Vector2f(0,1), Vector2f(1,0), Vector2f(0,-1), Vector2f(-1,0) };
	unsigned int id;
};

