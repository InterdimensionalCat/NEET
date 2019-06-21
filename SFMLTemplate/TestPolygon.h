#pragma once
#include "GameObject.h"
#include "TransformComp.h"
#include"PolygonSprite.h"
class TestPolygon :
	public GameObject
{
public:
	TestPolygon(Vector2f position, polygon body, Scene* master);
	~TestPolygon();
};

