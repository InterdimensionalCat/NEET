#pragma once
#ifndef game_h
#define game_h
#include "StateManager.h"
#include "Random.h"
#endif  // !game_h

class StateManager;
class GameState;

string GetCurrentWorkingDir(void);
RenderWindow* getGameWind();
Clock* getTimer();
int getFPS();

const int WIDTH = 1920;
const int HEIGHT = 1080;
extern bool debug;