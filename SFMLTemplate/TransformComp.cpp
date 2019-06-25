#include "stdafx.h"
#include "TransformComp.h"

int scale = 64;

TransformComp::TransformComp() : Component("Transform")
{
	changeShape({ Vector2f(0, 0), Vector2f(1, 0), Vector2f(1, 1), Vector2f(0, 1) });
}

TransformComp::TransformComp(Vector2f posIn) : Component("Transform")
{
	move(posIn);
	TransformComp();
}


TransformComp::~TransformComp()
{
}

void TransformComp::move(Vector2f velocity) {

	if (velocity.x < 0.05) velocity.x = 0.0f;
	if (velocity.y < 0.05) velocity.y = 0.0f;

	position += velocity;
	for (int i = 0; i < shape.points.size(); i++) {
		shape.points[i] = shape.points[i] + velocity;
	}
}

void TransformComp::changeShape(vector<Vector2f> points) {
	shape = polygon(points);
	for (int i = 0; i < shape.points.size(); i++) {
		shape.points.at(i) = ((float)scale * shape.points.at(i)) + position;
	}
}




