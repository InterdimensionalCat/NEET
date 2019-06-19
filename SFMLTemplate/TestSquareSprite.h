#pragma once
#include "Component.h"

class TestSquareSprite : Component
{
public:
	TestSquareSprite(Vector2f dimensions, Vector2f position, Color outlineColor);
	~TestSquareSprite();

	void onUpdate(float deltaTime, GameMouse* mouse, GameKeyboard* keyboard);
	void draw(RenderWindow* target);

	Vector2f dimensions;
	Vector2f position;
	Color color;
};

