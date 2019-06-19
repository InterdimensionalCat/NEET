#pragma once
#include "GameObject.h"

//contains, updates, and draws GameObjects

class Scene
{
public:
	Scene(string);
	~Scene();
	vector<GameObject*> objects;
	void onUpdate(float deltaTime, GameMouse* mouse, GameKeyboard* keyboard);
	void draw(RenderWindow* target);
	GameObject* createObject();
};

