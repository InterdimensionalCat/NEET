#pragma once
#include "Component.h"
#include "TransformComp.h"
#include "PolygonSprite.h"
#include "Scene.h"

class Scene;

class GameObject
{
public:
	GameObject(Scene* master);
	~GameObject();
	Scene* masterScene;
	vector<Component*> components;
	TransformComp* transform;
	void onUpdate(float deltaTime, GameMouse* mouse, GameKeyboard* keyboard);
	void draw(RenderWindow* target);
	void addComponent(Component* comp);
	Component* getComponent(string tagIn);

	void init() {
		for (auto comp : components) {
			comp->init();
		}
	}

	template <class T>

	T* getComponent() {
		for (auto comp : components) {
			if (dynamic_cast<T*>(comp)) {
				return (T*)comp;
			}
		}
		return NULL;
	}
};

