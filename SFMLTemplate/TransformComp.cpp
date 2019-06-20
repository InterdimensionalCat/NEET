#include "stdafx.h"
#include "TransformComp.h"

int scale = 64;

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

void TransformComp::changeShape(vector<Vector2f> points) {
	shape = polygon(points);
	for (int i = 0; i < shape.points.size(); i++) {
		shape.points.at(i) = (float)scale * (shape.points.at(i) + position);
	}
}




