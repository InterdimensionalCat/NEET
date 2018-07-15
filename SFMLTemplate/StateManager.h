#pragma once
#include "State.h"
#include <SFML\Graphics.hpp>
#include <algorithm>
#include "MenuState.h"

//The StateManager class manages the different states of the game(MenuState, GameState, potentially an interface or overworld state eventually)

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