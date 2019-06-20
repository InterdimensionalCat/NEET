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
	comp->masterObj = this;
	components.push_back(comp);
}

//https://stackoverflow.com/questions/37578849/how-to-index-all-the-derived-components-in-a-base-component-list-in-entity/37580620#37580620