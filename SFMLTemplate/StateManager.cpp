#pragma once
#include "stdafx.h"
#include "StateManager.h"
#include "State.h"
#include <iostream>
#include <string>

StateManager::StateManager() 
{
	//sets the default state to the main menu
	MenuState* menu = new MenuState();
	currentState = (State*)menu;
	currentState->init();
}

StateManager::~StateManager() 
{

}


void StateManager::onUpdate(float deltaTime) {
	currentState->onUpdate(deltaTime);
}

void StateManager::changeState(State* newCurrent) {
	currentState->exit();
	currentState = newCurrent;
	currentState->enter();
}

void StateManager::draw(sf::RenderWindow* window, double interpol) {
	currentState->draw(window, interpol);
}

State* StateManager::getCurrentState() {
	return currentState;
}

//these two methods allow single button presses to be checkable in real time without messing with the message loo[ (window events are garbo)

bool StateManager::isKeyPressed(sf::Keyboard::Key key) {
	return std::find(pressedKeys.begin(), pressedKeys.end(), key) != pressedKeys.end();
}

bool StateManager::isButtonPressed(sf::Mouse::Button button) {
	return std::find(pressedButtons.begin(), pressedButtons.end(), button) != pressedButtons.end();
}