#pragma once
#include "StateManager.h"

class StateManager;
class GameState;


std::string GetCurrentWorkingDir(void);
sf::RenderWindow* getGameWind();
StateManager* getManager();
GameState* getGame();
const int WIDTH = 1920;
const int HEIGHT = 1080;
extern bool debug;
