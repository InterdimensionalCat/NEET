#pragma once

#include <SFML\graphics.hpp>
#include "Game.h"

class BackgroundLayer
{
public:
	BackgroundLayer(uint16_t id);
	~BackgroundLayer();
	void draw(sf::RenderWindow* window, double interpol);
	void move(sf::Vector2f movement);
	sf::Texture* texture;
	sf::Sprite* layer1;
	float speed;
};

