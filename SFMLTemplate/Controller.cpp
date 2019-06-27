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
		body->velocity += speed * Vector2f(1, 0);
	}

	if (keyboard->isKeyDown(Keyboard::A)) {
		body->velocity -= speed * Vector2f(1, 0);
	}

	if (keyboard->isKeyPressed(Keyboard::Space)) {
		body->velocity -= jump * Vector2f(0, 1);
	}
}


