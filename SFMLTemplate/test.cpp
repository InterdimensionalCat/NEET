#pragma once
#include"stdafx.h"
#include"test.h"
#include "Scene.h"
#include "GameObject.h"
#include"TestPolygon.h"

void inputTest(GameMouse* mouse, GameKeyboard* keyboard) {

	cout << "Keys Pressed:" << endl;

	for (Keyboard::Key key : keyboard->pressedKeys) {
		cout << key << endl;
	}

	cout << "Buttons Pressed:" << endl;

	for (Mouse::Button button : mouse->pressedButtons) {
		cout << button << endl;
	}
}

Scene* PhysicsTest() {
	Scene* testScene = new Scene("physics test");
	vector<Vector2f> points = { Vector2f(0, 0), Vector2f(1, 0), Vector2f(1, 1), Vector2f(0, 1) };
	testScene->createObject(new TestPolygon(Vector2f(100, 400), polygon(points), testScene, "test"));
	/*points = { Vector2f(0, 0), Vector2f(0.5f, 0.6f), Vector2f(1, 1), Vector2f(0, 1) };
	testScene->createObject(new TestPolygon(Vector2f(200, 200), polygon(points), testScene, "test"));*/
	points = { Vector2f(0, 0), Vector2f(0.3f,0.1f), Vector2f(1, 1), Vector2f(0, 1) };
	GameObject* ground = new TestPolygon(Vector2f(100, 500), polygon(points), testScene, "ground");
	ground->transform->changeShape(points, Vector2f(100, 800), Vector2f(128, 64));
	RigidBody* body = ground->getComponent<RigidBody>();
	body->setGravity(false);
	//body->velocity += Vector2f(0, -25.0f);
	testScene->createObject(ground);
	return testScene;
}

void castTest() {
	A* atest = new B();
	if (B* btest = dynamic_cast<B*>(atest)) {
		cout << "success";
	}
}