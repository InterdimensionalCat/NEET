#include "stdafx.h"
#include "GameObject.h"


GameObject::GameObject()
{

}


GameObject::~GameObject()
{

}

void GameObject::onUpdate(float deltaTime, GameMouse* mouse, GameKeyboard* keyboard) {
	for (auto comp : components) {
		comp->onUpdate(deltaTime, mouse, keyboard);
	}
}

void GameObject::draw(RenderWindow* target) {
	for (auto comp : components) {
		comp->draw(target);
	}
}

void GameObject::addComponent(Component* comp) {
	components.push_back(comp);
}