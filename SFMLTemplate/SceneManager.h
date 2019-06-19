#pragma once
#include "Scene.h"

class SceneManager
{
public:
	SceneManager(string name);
	~SceneManager();
	Scene* currentScene;

	void load(string name);
};

