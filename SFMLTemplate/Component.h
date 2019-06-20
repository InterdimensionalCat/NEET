#pragma once
#include "GameObject.h"

//class GameObject

template <class T>

class Component
{
public:
	Component(string tag);
	~Component();

	T t;
	void addNewComponent() {

	}

	virtual void onUpdate(float deltaTime, GameMouse* mouse, GameKeyboard* keyboard);
	virtual void draw(RenderWindow* target);

	string tag;
	//GameObject* masterObj;
};

