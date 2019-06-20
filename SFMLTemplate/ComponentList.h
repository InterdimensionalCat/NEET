#pragma once
#include "stdafx.h"
#include "TransformComp.h"

template <class T>

class Component
{
public:
	T t;
	void adNewComponent() {

	}
};

class Mesh {
public:
	Mesh() {}
};

class Rigidbody {
public:
	Rigidbody() {}
	void AddForce(float x, float y, float z) {}
	void AddForce(Vector2f force) {}
};


class Transform {
public:
	Transform() {}
};

class Object {

};

class GameObject :Object,
	Component<Mesh>,
	Component<Rigidbody>,
	Component<TransformComp>
{
public:
	template <class T>
	T &GetComponent()
	{
		return this->Component<T>::t;
	}

	template <class T>
	T &AddComponent() {
		this->Component<T>::adNewComponent();
		return this->Component<T>::t;
	}
};

