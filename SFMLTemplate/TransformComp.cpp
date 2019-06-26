#include "stdafx.h"
#include "TransformComp.h"

int scale = 64;

TransformComp::TransformComp() : Component("Transform")
{
	changeShape({ Vector2f(0, 0), Vector2f(1, 0), Vector2f(1, 1), Vector2f(0, 1) }, Vector2f(0,0));
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

	position += velocity;
	for (int i = 0; i < shape.points.size(); i++) {
		shape.points[i] = shape.points[i] + velocity;
	}
}

void TransformComp::changeShape(vector<Vector2f> points, Vector2f position) {
	TransformComp::position = position;
	shape = polygon(points);
	for (int i = 0; i < shape.points.size(); i++) {
		shape.points.at(i) = ((float)scale * shape.points.at(i)) + position;
	}
	shape.normals = shape.calculateNormals(shape.points);
}

void TransformComp::changeShape(vector<Vector2f> points, Vector2f position, Vector2f scale) {
	TransformComp::position = position;
	shape = polygon(points);
	for (int i = 0; i < shape.points.size(); i++) {
		shape.points.at(i) = Vector2f(scale.x * shape.points.at(i).x + position.x, scale.y * shape.points.at(i).y + position.y);
	}
	shape.normals = shape.calculateNormals(shape.points);
}




