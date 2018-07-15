#pragma once
#include "State.h"
#include "MenuButton.h"
#include "stdafx.h"
#include <string>
#include<SFML\Graphics.hpp>
#include "Game.h"
#include <iostream>
class MenuState : State
{
public:
	MenuState();
	~MenuState();
	void onUpdate(float deltaTime) override;
	void init() override;
	void enter() override;
	void draw(sf::RenderWindow* window, double interpol) override;
	void exit() override;
	void select();
	std::string getName();
	MenuButton* options [3];
	int16_t currentSelection;
};

