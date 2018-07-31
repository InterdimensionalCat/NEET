#pragma once
#include "Entity.h"
#include "Tile.h"

class Tile;

//Class defines an actor that is capible of moving (a Mobile Entity), as with entity, mobs cannot be drawn to the screen

class Mob : public Entity
{
public:
	Mob(float posX, float posY, float sizeX, float sizeY/*, Animation* defaultAnimation*/);
	~Mob();
	virtual void move();
	virtual void onUpdate(float deltaTime) override;
	sf::Vector2f* motion;
	//bool isAerial	
	//sf::FloatRect getDefaultAABB();
	//unsigned int rotation; //can be 0, 1, 2, or 3;
	//float motionX;
	//float motionY;
	//virtual void draw(sf::RenderWindow* window, double interpol) override;
	//void rotate();

};

