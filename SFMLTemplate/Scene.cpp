#include "stdafx.h"
#include "Scene.h"


Scene::Scene(string name)
{
	engine = new PhysicsEngine(this);
}


Scene::~Scene()
{
}


void Scene::onUpdate(float deltaTime, GameMouse* mouse, GameKeyboard* keyboard) {
	for (auto obj : objects) {
		obj->onUpdate(deltaTime, mouse, keyboard);
	}

	engine->step(deltaTime);
}

void Scene::draw(RenderWindow* target) {
	for (auto obj : objects) {
		obj->draw(target);
	}
}

GameObject* Scene::createObject(GameObject* result) {
	objects.push_back(result);
	return result;
}