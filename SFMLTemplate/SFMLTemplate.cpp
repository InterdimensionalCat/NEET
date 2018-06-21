// SFMLTemplate.cpp : Defines the entry point for the console application.
//
#pragma once
#include "stdafx.h"
#include<SFML\Graphics.hpp>
#include <iostream>
#include "SFMLTemplate.h"
#include "StateManager.h"
#include "State.h"
#include "GameState.h"
#include "INitAnimations.h"

/////////////////////// FILE PATH STUFF ////////////////////////

#include <stdio.h>  /* defines FILENAME_MAX */
#define WINDOWS  /* uncomment this line to use it for windows.*/ 
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif
#include<iostream>




std::string GetCurrentWorkingDir(void) {
	char buff[FILENAME_MAX];
	GetCurrentDir(buff, FILENAME_MAX);
	std::string current_working_dir(buff);
	return current_working_dir;
}


/////////////////////////////////////////////////////////////////


void onUpdate(float deltaTime);
void draw(sf::RenderWindow* window, double interpol);

sf::RenderWindow* window;
StateManager* manager;
GameState* gameState;
bool debug = false;


int main()
{
	window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "LMAO EZ");
	window->setFramerateLimit(60);
	window->setKeyRepeatEnabled(false);
	manager = new StateManager();
	gameState = new GameState();
	gameState->init();
	InitAnimations();

	sf::Clock clock;
	sf::Clock c1;
	uint16_t tps = 0;
	uint16_t fps = 0;

	while (window->isOpen()) {

		//handle events and stuff

		sf::Event event;

		manager->pressedButtons.clear();
		manager->pressedKeys.clear();

		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();

			if (event.type == sf::Event::MouseButtonPressed)
			{

				manager->pressedButtons.push_back(event.mouseButton.button);

			}

			if (event.type == sf::Event::KeyPressed) {

				manager->pressedKeys.push_back(event.key.code);

				if (event.key.code == sf::Keyboard::I) {
					debug = !debug;
				}
			}
		}

		//update game logic
		float deltaTime = clock.getElapsedTime().asSeconds();
		if (deltaTime > 0.001666666f) {
			clock.restart();
			onUpdate(deltaTime);
			tps++;
		}

		if (c1.getElapsedTime().asSeconds() >= 1) {
			c1.restart();
			if (debug) {
				std::cout << "tps: " << tps << " fps: " << fps << std::endl;
			}
			tps = 0;
			fps = 0;
		}

		window->clear(sf::Color(255,255,255,255));

		//draw objects

		draw(window, clock.getElapsedTime().asSeconds() * 60);

		fps++;
		window->display();
	}


    return 0;
}

//deltatime is in seconds
void onUpdate(float deltaTime) {

	if(deltaTime > 0.02&&debug) 	std::cout << "abnormally high time elapsed since last tick:" << deltaTime << " seconds elapsed." << std::endl;

	manager->onUpdate(deltaTime);
}

void draw(sf::RenderWindow* window, double interpol) {
	//std::cout << interpol << std::endl;
	manager->draw(window, interpol);

}

sf::RenderWindow* getGameWind() {
	return window;
}

StateManager* getManager() {
	return manager;
}

GameState* getGame() {
	return gameState;
}
