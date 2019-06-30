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

	//change position to COM

	TransformComp::position = centroid(shape.points);
}

void TransformComp::changeShape(Vector2f position, Vector2f scale) {
	TransformComp::position = position;
	shape = polygon();
	shape.points = { Vector2f(0,0), Vector2f(1,0), Vector2f(1,1), Vector2f(0,1), };
	for (int i = 0; i < shape.points.size(); i++) {
		shape.points.at(i) = Vector2f(scale.x * shape.points.at(i).x + position.x, scale.y * shape.points.at(i).y + position.y);
	}
	shape.normals = shape.calculateNormals(shape.points);

	//change position to COM

	TransformComp::position = centroid(shape.points);
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

//origin of local bounds is COM of object

vector<Vector2f> TransformComp::localBounds() {
	return localBounds(shape.points, Vector2f(0,0));
}
vector<Vector2f> TransformComp::localBounds(vector<Vector2f> other, Vector2f centTrans) {
	vector<Vector2f> outp;
	for (auto vec : other) {
		outp.push_back(vec - position - centTrans);
	}

	return outp;
}

void TransformComp::rotate(float radians) {
	vector<Vector2f> localB = localBounds();
	matrix rotate(radians);
	for (int i = 0; i < shape.points.size(); i++) {
		shape.points[i] = rotate*localB[i] + position;
	}
}




