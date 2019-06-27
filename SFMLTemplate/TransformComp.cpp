#include "stdafx.h"
#include "TransformComp.h"

TransformComp::TransformComp()
{
	changeShape({ Vector2f(0, 0), Vector2f(1, 0), Vector2f(1, 1), Vector2f(0, 1) }, Vector2f(0,0), Vector2f(100,100));
}

TransformComp::TransformComp(Vector2f posIn)
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

//this should always be called on a new transform

void TransformComp::changeShape(vector<Vector2f> points, Vector2f position, Vector2f scale) {
	TransformComp::position = position;
	shape = polygon();
	shape.points = points;
	for (int i = 0; i < shape.points.size(); i++) {
		shape.points.at(i) = Vector2f(scale.x * shape.points.at(i).x + position.x, scale.y * shape.points.at(i).y + position.y);
	}
	shape.normals = shape.calculateNormals(shape.points);
}

void TransformComp::changeShape(Vector2f position, Vector2f scale) {
	TransformComp::position = position;
	shape = polygon();
	shape.points = { Vector2f(0,0), Vector2f(1,0), Vector2f(1,1), Vector2f(0,1), };
	for (int i = 0; i < shape.points.size(); i++) {
		shape.points.at(i) = Vector2f(scale.x * shape.points.at(i).x + position.x, scale.y * shape.points.at(i).y + position.y);
	}
	shape.normals = shape.calculateNormals(shape.points);
}




