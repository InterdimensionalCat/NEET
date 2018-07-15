#pragma once
#include "Entity.h"
#include "Tile.h"

class Tile;

class Mob : public Entity
{
public:
	Mob(float posX, float posY, float sizeX, float sizeY, Animation* defaultAnimation);
	virtual void move();
	void virtual onUpdate(float deltaTime) override;
	sf::Vector2f* motion;
	//float motionX;
	//float motionY;
	bool isAerial;
	virtual void draw(sf::RenderWindow* window, double interpol) override;
	virtual bool onVerticalCollision(sf::FloatRect intersectRect, Tile* tileIn) override;
	virtual bool onHorizontalCollision(sf::FloatRect intersectRect, Tile* tileIn) override;
	~Mob();
};

