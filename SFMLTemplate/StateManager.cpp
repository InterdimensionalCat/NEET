#pragma once
#include "stdafx.h"
#include "StateManager.h"
#include "State.h"
#include <iostream>
#include <string>

StateManager::StateManager() 
{
	MenuState* menu = new MenuState();
	currentState = (State*)menu;
	currentState->init();
}

StateManager::~StateManager() 
{

}


void StateManager::onUpdate(float deltaTime) {
	//std::cout << "Updating state " << menu->getName() << std::endl;
	currentState->onUpdate(deltaTime);
	//leftClick = false;
	//wClick = false;
	//sClick = false;
}

void StateManager::changeState(State* newCurrent) {
	currentState->exit();
	currentState = newCurrent;
	currentState->enter();
}

void StateManager::draw(sf::RenderWindow* window, double interpol) {
	//std::cout << "Drawing state " << menu->getName() << std::endl;
	currentState->draw(window, interpol);
}

State* StateManager::getCurrentState() {
	return currentState;
}

bool StateManager::isKeyPressed(sf::Keyboard::Key key) {
	return std::find(pressedKeys.begin(), pressedKeys.end(), key) != pressedKeys.end();
}

bool StateManager::isButtonPressed(sf::Mouse::Button button) {
	return std::find(pressedButtons.begin(), pressedButtons.end(), button) != pressedButtons.end();
}