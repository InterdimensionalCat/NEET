#pragma once
#include"stdafx.h"
#include"test.h"

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