#include "stdafx.h"
#include "GameKeyboard.h"


GameKeyboard::GameKeyboard(RenderWindow* currentWindow)
{
	//causes keypresses to only send 1 event
	currentWindow->setKeyRepeatEnabled(false);
	GameKeyboard::currentWindow = currentWindow;
}


GameKeyboard::~GameKeyboard()
{
}

void GameKeyboard::updateInput(Keyboard::Key key) {
	pressedKeys.push_back(key);
}

bool GameKeyboard::isKeyPressed(Keyboard::Key key) {
	return find(pressedKeys.begin(), pressedKeys.end(), key) != pressedKeys.end();
}

bool GameKeyboard::isKeyDown(Keyboard::Key key) {
	return Keyboard::isKeyPressed(key);
}