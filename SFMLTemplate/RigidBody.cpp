#include "stdafx.h"
#include "RigidBody.h"


RigidBody::RigidBody(string material)
{
	mat = generateMaterial(material);

}

void RigidBody::init() {
	masterObj->masterScene->engine->addBody(this);
	setGravity(true);
}

RigidBody::~RigidBody()
{

}

void RigidBody::onUpdate(float deltaTime, GameMouse* mouse, GameKeyboard* keyboard) {

	//Vector2f newPos = masterObj->transform->position + velocity;
	//masterObj->transform->move(newPos);
}

