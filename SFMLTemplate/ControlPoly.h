#pragma once
#include "GameObject.h"
#include "TransformComp.h"
#include"PolygonSprite.h"
#include "Controller.h"

class ControlPoly :
	public GameObject
{
public:
	ControlPoly(Vector2f position, Scene* master);
	~ControlPoly();
};

