#pragma once
#include "Component.h"
#include "TransformComp.h"
#include "PolygonSprite.h"

template <typename T>

class GameObject : Component<TransformComp>, Component<PolygonSprite>
{
public:
	GameObject();
	~GameObject();
	//vector<Component*> components;
	void onUpdate(float deltaTime, GameMouse* mouse, GameKeyboard* keyboard);
	void draw(RenderWindow* target);
	//void addComponent(Component* comp);
	//Component* getComponent(string tagIn);

	template <class T>
	T &GetComponent()
	{
		return this->Component<T>::t;
	}

	template <class T>
	T &AddComponent() {
		this->Component<T>::addNewComponent();
		return this->Component<T>::t;
	}



	//T* getComponent(string stringIn) {
	//	T* result = NULL;
	//	
	//}

	//Component* GameObject::getComponent(string tagIn) {
	//	Component* result = NULL;
	//	for (auto comp : components) {
	//		if (comp->tag == tagIn) result = comp;
	//	}
	//	return result;
	//}
};

