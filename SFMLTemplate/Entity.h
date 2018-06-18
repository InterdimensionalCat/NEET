#pragma once
#include <SFML\graphics.hpp>
#include "SFMLTemplate.h"
#include <string>
#include <iostream>
#include "Tile.h"

class Tile;

class Entity
{
public:
	Entity(float posX, float posY, std::string textureName, float sizeX, float sizeY);
	~Entity();
	virtual void onUpdate(float deltaTime);
	virtual void draw(sf::RenderWindow* window, double interpol);
	virtual void animate();
	virtual void spawn();
	virtual void setDead();
	virtual bool onVerticalCollision(sf::FloatRect intersectRect, Tile* tileIn);
	virtual bool onHorizontalCollision(sf::FloatRect intersectRect, Tile* tileIn);
	sf::FloatRect* AABB;
	sf::Vector2f* pos;
	//float posX;
	//float posY;
	sf::Texture texture;
	sf::Sprite sprite;
};

