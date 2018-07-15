#pragma once

#include <string>
#include <SFML\Graphics.hpp>

//The State class is essentially an interface: it is never meant to be instantiated on its own, it is inherited by all other state types

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

