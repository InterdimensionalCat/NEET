#pragma once
#include"stdafx.h"
#include"test.h"
#include "Scene.h"
#include "GameObject.h"
#include"TestSquare.h"

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
	testScene->createObject((GameObject*)new TestSquare(Vector2f(100, 100), Vector2f(100, 100)));
	return testScene;
}