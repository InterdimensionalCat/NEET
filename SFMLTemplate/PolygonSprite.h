#pragma once
#include "Component.h"
#include "stdafx.h"
#include "TransformComp.h"

class PolygonSprite : public Component
{
public:
	PolygonSprite(Color outlineColor);
	~PolygonSprite();

	void onUpdate(float deltaTime, GameMouse* mouse, GameKeyboard* keyboard);
	void draw(RenderWindow* target);
	void init();

	Color color;
	TransformComp* transform;
};

