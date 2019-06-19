#pragma once
#include "Component.h"
class GameObject
{
public:
	GameObject();
	~GameObject();
	vector<Component*> components;
	void onUpdate(float deltaTime, GameMouse* mouse, GameKeyboard* keyboard);
	void draw(RenderWindow* target);
	void addComponent(Component* comp);
	Component* getComponent(string tagIn);
};

