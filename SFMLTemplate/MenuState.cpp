#include "stdafx.h"
#include "MenuState.h"
#include "MenuButton.h"
#include "Game.h"
#include <iostream>

MenuState::MenuState()
{

}


MenuState::~MenuState()
{

}


void MenuState::onUpdate(float deltaTime) {

	//Polls keyboard and mouse to determine what button on the menu is selected

	//if (getManager()->isKeyPressed(sf::Keyboard::W)) {
	//	currentSelection--;
	//	if (currentSelection < 0) {
	//		currentSelection = 2;
	//	}
	//}

	//if (getManager()->isKeyPressed(sf::Keyboard::S)) {
	//	currentSelection++;
	//	if (currentSelection > 2) {
	//		currentSelection = 0;
	//	}
	//}

	//if (getManager()->isButtonPressed(sf::Mouse::Left))
	//{
	//	sf::Vector2i mousePos = sf::Mouse::getPosition(*getGameWind());

	//	for (uint16_t i = 0; i < sizeof(options) / sizeof(options[0]); i++) {
	//		if (options[i]->AABB.contains(mousePos)) {
	//			currentSelection = i;
	//			select();
	//		}
	//	}
	//}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
		select();
	}

	for (int i = 0; i < sizeof(options) / sizeof(options[0]); i++) {
		if (currentSelection == i) {
			options[i]->selected = true;
		} else {
			options[i]->selected = false;
		}
	}
}

void MenuState::init() {
	options[0] = new MenuButton("GrassTile", "grassSlopeLeft", "PLAY", 1920 / 2 - 64, 200);
	options[1] = new MenuButton("GrassTile", "grassSlopeLeft", "OPTIONS", 1920 / 2 - 64, 400);
	options[2] = new MenuButton("GrassTile", "grassSlopeLeft", "EXIT", 1920 / 2 - 64, 600);
	for (MenuButton* b : options) {
		b->init();
	}
	currentSelection = 0;
	options[0]->selected = true;
}

void MenuState::enter() {

}

void MenuState::select() {
	switch (currentSelection) {
	case 0:
		std::cout << "Play" << std::endl;
		/*getManager()->changeState((State*)getGame());*/
		break;
	case 1:
		std::cout << "Options" << std::endl;
		break;
	case 2:
		std::cout << "Exit" << std::endl;
		break;
	}
}

void MenuState::draw(sf::RenderWindow* window, double interpol) {
	for (MenuButton* button : options) {
		button->draw(window, interpol);
	}
}

void MenuState::exit() {

}

std::string MenuState::getName() {
	return "MENU";
}