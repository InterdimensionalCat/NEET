#pragma once
#include "Component.h"
#include "stdafx.h"
#include "TransformComp.h"

class PolygonSprite
{
public:
	PolygonSprite(Color outlineColor);
	~PolygonSprite();

	void onUpdate(float deltaTime, GameMouse* mouse, GameKeyboard* keyboard);
	void draw(RenderWindow* target);

	polygon body;
	Vector2f position;
	Color color;
};

