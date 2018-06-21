#pragma once
#include "State.h"
#include <SFML\Graphics.hpp>
#include <algorithm>
#include "MenuState.h"

class StateManager {
public:
	StateManager();
	~StateManager();
	void onUpdate(float deltaTime);
	void changeState(State* newCurrent);
	State* getCurrentState();
	void draw(sf::RenderWindow* window, double interpol);
	State* currentState;
	bool isKeyPressed(sf::Keyboard::Key key);
	bool isButtonPressed(sf::Mouse::Button button);
	std::vector<sf::Keyboard::Key> pressedKeys;
	std::vector<sf::Mouse::Button> pressedButtons;
};