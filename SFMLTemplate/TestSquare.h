#pragma once
#include "GameObject.h"
#include "TransformComp.h"
#include"TestSquareSprite.h"
class TestSquare :
	public GameObject
{
public:
	TestSquare(Vector2f position, Vector2f dimensions);
	~TestSquare();
};

