#include "stdafx.h"
#include "Controller.h"


Controller::Controller()
{
}

void Controller::init() {
	body = masterObj->getComponent<RigidBody>();
}

Controller::~Controller()
{

}

void Controller::onUpdate(float deltaTime, GameMouse* mouse, GameKeyboard* keyboard) {
	if (keyboard->isKeyDown(Keyboard::D)) {
		body->force += speed * Vector2f(1, 0);
	}

	if (keyboard->isKeyDown(Keyboard::A)) {
		body->force -= speed * Vector2f(1, 0);
	}

	if (keyboard->isKeyPressed(Keyboard::Space)) {
		body->force -= jump * Vector2f(0, 1);
	}

	//masterObj->transform->rotate(3.14159f / 16.0f);
}


