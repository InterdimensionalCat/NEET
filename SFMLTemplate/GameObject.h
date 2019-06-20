#pragma once
#include "Component.h"
#include "TransformComp.h"
#include "PolygonSprite.h"

class GameObject
{
public:
	GameObject();
	~GameObject();
	vector<Component*> components;
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

	T* getComponent(string tagIn) {
		//T* result = NULL;
		for (auto comp : components) {
			//if (T->tag != tagIn) continue;
			if (dynamic_cast<T*>(comp)) {
				//return result;
				return (T*)comp;
			}
		}
		//return result;
		return NULL;
	}
};

