#pragma once
#include "stdafx.h"

class GameMouse
{
public:
	GameMouse(RenderWindow* currentWindow);
	~GameMouse();
	RenderWindow* currentWindow;
	std::vector<Mouse::Button> pressedButtons;


	void updateInput(Mouse::Button button);
	bool isButtonPressed(Mouse::Button button);
	bool isButtonDown(Mouse::Button button);
};

