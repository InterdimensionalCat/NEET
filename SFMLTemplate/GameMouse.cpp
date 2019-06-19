#include "stdafx.h"
#include "GameMouse.h"


GameMouse::GameMouse(RenderWindow* currentWindow)
{
	GameMouse::currentWindow = currentWindow;
}


GameMouse::~GameMouse()
{
}

void GameMouse::updateInput(Mouse::Button button) {
	pressedButtons.push_back(button);
}

bool GameMouse::isButtonPressed(Mouse::Button button) {
	return std::find(pressedButtons.begin(), pressedButtons.end(), button) != pressedButtons.end();
}

bool  GameMouse::isButtonDown(Mouse::Button button) {
	return Mouse::isButtonPressed(button);
}
