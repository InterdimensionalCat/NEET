#pragma once
#include "GameObject.h"
#include "PhysicsEngine.h"

class PhysicsEngine;

//contains, updates, and draws GameObjects

class Scene
{
public:
	Scene(string);
	~Scene();
	vector<GameObject*> objects;
	void onUpdate(float deltaTime, GameMouse* mouse, GameKeyboard* keyboard);
	void draw(RenderWindow* target);
	GameObject* createObject(GameObject* result);
	PhysicsEngine* engine;
};

