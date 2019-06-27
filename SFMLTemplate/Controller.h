#pragma once
#include "Component.h"
class Controller :
	public Component
{
public:
	Controller();
	~Controller();

	RigidBody* body;
	float speed = 1.0f;
	float jump = 25.0f;

	void onUpdate(float deltaTime, GameMouse* mouse, GameKeyboard* keyboard);
	void init();
};

