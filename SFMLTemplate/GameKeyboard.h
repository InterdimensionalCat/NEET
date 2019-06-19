#pragma once
#include "stdafx.h"
class GameKeyboard
{
public:
	GameKeyboard(RenderWindow* currentWindow);
	~GameKeyboard();
	RenderWindow* currentWindow;
	std::vector<Keyboard::Key> pressedKeys;


	void updateInput(Keyboard::Key key);
	bool isKeyPressed(Keyboard::Key key);
	bool isKeyDown(Keyboard::Key key);
};

