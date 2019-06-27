#include "stdafx.h"
#include "GameObject.h"


GameObject::GameObject(Scene* master)
{
	masterScene = master;
	transform = new TransformComp();
	addComponent(transform);
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