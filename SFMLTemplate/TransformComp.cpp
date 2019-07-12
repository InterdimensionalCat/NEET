#include "stdafx.h"
#include "TransformComp.h"

TransformComp::TransformComp()
{
	changeShape({ Vector2f(0, 0), Vector2f(1, 0), Vector2f(1, 1), Vector2f(0, 1) }, Vector2f(0,0), Vector2f(100,100), 0.0f);
}

TransformComp::TransformComp(Vector2f posIn)
{
	move(posIn, 0.0f);
	TransformComp();
	
}


TransformComp::~TransformComp()
{
}

void TransformComp::move(Vector2f velocity, float angularVelocity) {
	position += velocity;
	rotate(angularVelocity);
}

//this should always be called on a new transform

void TransformComp::changeShape(vector<Vector2f> points, Vector2f position, Vector2f scale, float rotation) {
	TransformComp::position = position;
	shape = polygon();
	shape.points = points;
	rotate(angle);
	for (int i = 0; i < shape.points.size(); i++) {
		shape.points.at(i) = Vector2f(scale.x * shape.points.at(i).x, scale.y * shape.points.at(i).y);
	}
	shape.normals = shape.calculateNormals(shape.points);

	//change position to COM

	TransformComp::position = centroid(shape.points);

	for (int i = 0; i < shape.points.size(); i++) {
		shape.points.at(i) -= TransformComp::position;
	}
}

void TransformComp::changeShape(Vector2f position, Vector2f scale, float rotation) {
	changeShape({ Vector2f(0,0), Vector2f(1,0), Vector2f(1,1), Vector2f(0,1) }, position, scale, rotation);
}

AABB TransformComp::getMinAABB() {

	float minX = FLT_MAX;
	float minY = FLT_MAX;
	float maxX = -FLT_MAX;
	float maxY = -FLT_MAX;

	for (auto point : shape.points) {
		if (point.x > maxX) maxX = point.x;
		if (point.x < minX) minX = point.x;
		if (point.y > maxY) maxY = point.y;
		if (point.y < minY) minY = point.y;
	}

	return AABB(Vector2f(minX, minY), Vector2f(maxX, maxY));
}


void TransformComp::rotate(float radians) {

	angle += radians;
	orient = matrix(radians);
}




