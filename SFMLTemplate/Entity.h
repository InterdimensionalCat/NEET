#pragma once
#include <SFML\graphics.hpp>
#include "Game.h"
#include <string>
#include <iostream>
#include "Tile.h"
#include "Animation.h"

class Tile;

//Base class for an Entity (or actor), note that entity does not natively support being drawn to the screen (only classes that inherit sf::Drawable can be drawn to the screen

class Entity
{
public:
	Entity(float posX, float posY, float sizeX, float sizeY/*, Animation* defaultAnimation*/);
	~Entity();
	virtual void onUpdate(float deltaTime);
	//virtual void draw(sf::RenderWindow* window, double interpol);
	virtual void spawn();
	virtual void setDead();
	virtual void onCollision(Entity* collided);
	sf::FloatRect* AABB;
	sf::Vector2f* pos;
	float sizeX;
	float sizeY;
	//Animation* currentAnimation;
};

