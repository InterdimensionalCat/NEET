#pragma once
#include "State.h"
#include "Level.h"
#include "Game.h"
#include "Entity.h"
#include "Player.h"
#include "BackgroundEngine.h"
#include "BasicGun.h"

class Entity;
class Player;
class BasicGun;

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
	void registerDrawable(sf::Drawable* target);
	std::string getName();
	float getZoom();
	sf::FloatRect* getRenderArea();
	sf::FloatRect* renderArea;
	BackgroundEngine* pEngine;
};

