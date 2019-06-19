#include "stdafx.h"
#include "GameObject.h"


GameObject::GameObject()
{

}


GameObject::~GameObject()
{

}

void GameObject::onUpdate(float deltaTime, GameMouse* mouse, GameKeyboard* keyboard) {

}

void GameObject::draw(RenderWindow* target) {
	for (auto comp : components) {
		
	}
}

void GameObject::addComponent(Component comp) {

}

Component* GameObject::getComponent(string tagIn) {
	Component* result = NULL;
	for (auto comp : components) {
		if (comp->tag == tagIn) result = comp;
	}
	return result;
}