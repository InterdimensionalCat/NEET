#include "stdafx.h"
#include "Component.h"


Component::Component(string tag)
{
	Component::tag = tag;
}


Component::~Component()
{

}

void Component::onUpdate(float deltaTime, GameMouse* mouse, GameKeyboard* keyboard) {

}

void Component::draw(RenderWindow* target) {

}

void Component::init() {

}


