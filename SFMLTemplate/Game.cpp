// SFMLTemplate.cpp : Defines the entry point for the console application.
//
#pragma once
#include "stdafx.h"
#include<SFML\Graphics.hpp>
#include <iostream>
#include "Game.h"
#include "StateManager.h"
#include "State.h"
#include "GameState.h"
#include "INitAnimations.h"

/////////////////////// FILE PATH STUFF ////////////////////////

#include <stdio.h>  /* defines FILENAME_MAX */
#define WINDOWS
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

//prototypes that need to be used within Game.cpp, but not outside of it

void onUpdate(float deltaTime); 
void draw(sf::RenderWindow* window, double interpol);

//global variables

sf::RenderWindow* window;
StateManager* manager;
GameState* gameState;
bool debug = false;


int main()
{



	//Initialize some objects for the gameloop

	window = new sf::RenderWindow(/*sf::VideoMode::getFullscreenModes().at(0)*/sf::VideoMode(WIDTH, HEIGHT), "LMAO EZ"); //NB: TEXTURES CANNOT BE CREATED BEFORE THIS WINDOW IS INITIALIZED
	window->setFramerateLimit(60);
	//window->setVerticalSyncEnabled(true);

	//causes keypresses to only send 1 event

	window->setKeyRepeatEnabled(false);

	//More initialization

	manager = new StateManager();
	gameState = new GameState();
	gameState->init();
	InitAnimations();

	sf::Clock gameLoopTimer; //timer for gameloop updates, right now it is somewhat vestigial
	sf::Clock fpsTimer;      //timer that polls the fps and tps counter every second
	uint16_t tps = 0;
	uint16_t fps = 0;

	//Main game loop

	while (window->isOpen()) {

		//handle window events

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

		float deltaTime = gameLoopTimer.getElapsedTime().asSeconds();
		if (true/*deltaTime > 0.01666666f*/) { //need to look at this line
			gameLoopTimer.restart();
			onUpdate(deltaTime);
			tps++;
		}

		//allows the debugger to show the current frames per second and ticks per second

		if (fpsTimer.getElapsedTime().asSeconds() >= 1) {
			fpsTimer.restart();
			if (debug) {
				std::cout << "tps: " << tps << " fps: " << fps << std::endl;
			}
			tps = 0;
			fps = 0;
		}

		window->clear(sf::Color(255,255,255,255));

		//draw objects

		draw(window, gameLoopTimer.getElapsedTime().asSeconds() * 60);

		fps++;
		window->display();
	}


    return 0;
}

//deltatime is in seconds
void onUpdate(float deltaTime) {

	//called every tick: ANY function called onUpdate should be called every tick so long as the the parent object is initialized

	//if(deltaTime > 0.02&&debug) 	std::cout << "abnormally high time elapsed since last tick:" << deltaTime << " seconds elapsed." << std::endl;

	manager->onUpdate(deltaTime);
}

void draw(sf::RenderWindow* window, double interpol) {

	//called every frame

	manager->draw(window, interpol);

}

//getters for the game loop

sf::RenderWindow* getGameWind() {
	return window;
}

StateManager* getManager() {
	return manager;
}

GameState* getGame() {
	return gameState;
}
