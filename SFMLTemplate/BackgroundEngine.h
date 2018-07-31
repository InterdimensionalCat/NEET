#pragma once
#include <SFML\graphics.hpp>
#include "BackgroundLayer.h"



class BackgroundLayer;

class BackgroundEngine
{
public:
	BackgroundEngine(uint16_t numBG);
	~BackgroundEngine();
	void draw(sf::RenderWindow* window, double interpol);
	void move(sf::Vector2f movement);
	std::vector<BackgroundLayer> layers;
};

