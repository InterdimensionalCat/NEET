#pragma once
#include "State.h"
#include "Level.h"
#include "Game.h"
#include "Entity.h"
#include "Player.h"
#include "BackgroundEngine.h"

class Entity;
class Player;

class GameState : State
{
public:
	GameState();
	~GameState();
	Level* CurrentLevel;
	void onUpdate(float deltaTime);
	void init();
	void enter();
	void draw(sf::RenderWindow* window, double interpol);
	void exit();
	std::string getName();
	float getZoom();
	BackgroundEngine* pEngine;
};

