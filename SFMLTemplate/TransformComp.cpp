#include "stdafx.h"
#include "TransformComp.h"


TransformComp::TransformComp(Vector2f posIn) : Component("Transform")
{
	move(posIn);
}


TransformComp::~TransformComp()
{
}

void TransformComp::move(Vector2f newPos) {
	position = newPos;
}


