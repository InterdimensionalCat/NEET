// SFMLTemplate.cpp : Defines the entry point for the console application.
//

//GAMELOOP PURPOSE: Loop the game at a fixed timestep and send update and draw messages to the scene

#pragma once
#include "stdafx.h"
#include<SFML\Graphics.hpp>
#include <iostream>
#include "Game.h"
#include "SceneManager.h"

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


void onUpdate(float deltaTime, GameMouse* mouse, GameKeyboard* keyboard); 
void draw(RenderWindow* window, double interpol);
RenderWindow* window;
GameKeyboard* keyboard;
GameMouse* mouse;
SceneManager* manager;

Clock* globalTimer;
int numFPS = 0;
bool debug = false;

int main()
{

	window = new RenderWindow(VideoMode(WIDTH, HEIGHT), "Game Engine");
	window->setFramerateLimit(60);
	keyboard = new GameKeyboard(window);
	mouse = new GameMouse(window);
	uint16_t tps = 0;
	uint16_t fps = 0;
	Clock gameLoopTimer;
	Clock fpsTimer;
	float accumulator = 0;
	globalTimer = &gameLoopTimer;

	//Changes the speed of the game
	const float targetDT = 1.0f / 60.0f;

	manager = new SceneManager("gamestate");
	manager->currentScene = PhysicsTest();

	//Main game loop
	while (window->isOpen()) {

		//Clear last input

		//Update input
		Event event;
		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed)
				window->close();

			if (event.type == Event::MouseButtonPressed)
			{
				mouse->updateInput(event.mouseButton.button);
			}

			if (event.type == Event::KeyPressed) {
				keyboard->updateInput(event.key.code);
			}
		}

		//update game logic

		float deltaTime = gameLoopTimer.getElapsedTime().asSeconds();
		gameLoopTimer.restart();
		accumulator += deltaTime;
		if (accumulator > 2.0f) {
			accumulator = 2.0f;
		}

		while (accumulator > targetDT) {
			
			//updates the game
			onUpdate(targetDT, mouse, keyboard);
			accumulator -= targetDT;
			tps++;
		}


		if (fpsTimer.getElapsedTime().asSeconds() >= 1) {
			fpsTimer.restart();

			numFPS = fps;
			tps = 0;
			fps = 0;
		}

		window->clear(Color(255,255,255,255));


		//draws the game
		draw(window, gameLoopTimer.getElapsedTime().asSeconds() * 60);

		fps++;
		window->display();
	}
    return 0;
}


void onUpdate(float deltaTime, GameMouse* mouse, GameKeyboard* keyboard) {

	//deltatime is in seconds

	manager->currentScene->onUpdate(deltaTime, mouse, keyboard);

	mouse->pressedButtons.clear();
	keyboard->pressedKeys.clear();

}

void draw(sf::RenderWindow* window, double interpol) {

	//called every frame

	manager->currentScene->draw(window);

}

sf::RenderWindow* getGameWind() {
	return window;
}


sf::Clock* getTimer() {
	return globalTimer;
}

int getFPS() {
	return numFPS;
}