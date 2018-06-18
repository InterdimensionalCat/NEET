#pragma once

#include <string>
#include <SFML\Graphics.hpp>

class State
{
public:
	State();
	~State();
	virtual void onUpdate(float deltaTime);
	virtual void init();
	virtual void enter();
	virtual void draw(sf::RenderWindow* window, double interpol);
	virtual void exit();
	std::string getName();
};

