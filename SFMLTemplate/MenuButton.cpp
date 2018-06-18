#include "State.h"
#include "MenuButton.h"
#include "stdafx.h"
#include <string>
#include<SFML\Graphics.hpp>
#include "SFMLTemplate.h"
#include <iostream>


MenuButton::MenuButton(std::string unselected, std::string selected, std::string name, float posX, float posY)
{
	MenuButton::Sselected = selected;
	MenuButton::Sunselected = unselected;

	MenuButton::posX = posX;
	MenuButton::posY = posY;
	
	MenuButton::AABB = sf::IntRect((int)posX, (int)posY, 100, 100);

	MenuButton::selected = false;

	//init(unselected, selected);
}

void MenuButton::init() {

	if (!unselectedTexture.loadFromFile(GetCurrentWorkingDir() + "\\resources\\" + MenuButton::Sunselected + ".png")) {
		std::cout << "COULD NOT LOAD IMAGE" << std::endl;
	}
	if (!selectedTexture.loadFromFile(GetCurrentWorkingDir() + "\\resources\\" + MenuButton::Sselected + ".png")) {
		std::cout << "COULD NOT LOAD IMAGE" << std::endl;
	}

	unselectedSprite.setTexture(unselectedTexture);
	selectedSprite.setTexture(selectedTexture);
}


MenuButton::~MenuButton()
{
}

void MenuButton::draw(sf::RenderWindow* window, double interpol) {
	if (selected) {
		//draw selected sprite
		selectedSprite.setPosition(sf::Vector2f(posX, posY));
		window->draw(selectedSprite);
	} else {
		//draw unselected sprite
		unselectedSprite.setPosition(sf::Vector2f(posX, posY));
		window->draw(unselectedSprite);
	}
}
