#pragma once
#include "GameObject.h"

class GameObject;

class Component
{
public:
	Component(string tag);
	~Component();

	virtual void onUpdate(float deltaTime, GameMouse* mouse, GameKeyboard* keyboard);
	virtual void draw(RenderWindow* target);

	string tag;
	GameObject* masterObj;
};

