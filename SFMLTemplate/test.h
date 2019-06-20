#pragma once
#include "stdafx.h"
#include "Scene.h"

void inputTest(GameMouse* mouse, GameKeyboard* keyboard);
Scene* PhysicsTest();

class A {
public:
	A() {};
	virtual void doSomething() {}
};

class B : public A {
public:
	B() {};
	void doSomething() {}
};
void castTest();
