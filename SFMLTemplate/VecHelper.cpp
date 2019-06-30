#include "stdafx.h"
#include "VecHelper.h"


using namespace sf;

//returns the average of 2 floats

float Average(float a, float b) {
	return sqrt(a * a + b * b);
}


float mean(float a, float b) {
	return (a + b) / 2.0f;
}


float Distance(Vector2f a, Vector2f b)
{
	return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
}

float dotProduct(Vector2f a, Vector2f b) {
	return a.x * b.x + a.y * b.y;
}

Vector2f normalize(Vector2f vecIn) {
	float mag = magnitude(vecIn);
	if (mag > 0) {
		//vecIn.x /= mag;
		//vecIn.y /= mag;

		vecIn /= mag;
	}

	return vecIn;
}

float magnitude(Vector2f vecIn) {
	return sqrt(vecIn.x * vecIn.x + vecIn.y * vecIn.y);
}

// Two crossed vectors return a scalar
float CrossProduct(const Vector2f& a, const Vector2f& b)
{
	return a.x * b.y - a.y * b.x;
}

// More exotic (but necessary) forms of the cross product
// with a vector a and scalar s, both returning a vector
Vector2f CrossProduct(const Vector2f& a, float s)
{
	return Vector2f(s * a.y, -s * a.x);
}

Vector2f CrossProduct(float s, const Vector2f& a)
{
	return Vector2f(-s * a.y, s * a.x);
}

std::vector<Vector2f>* createPoly(Vector2f position, Vector2f dimensions) {
	std::vector<Vector2f>* vertices = new std::vector<sf::Vector2f>();
	vertices->push_back(Vector2f(position.x + dimensions.x, position.y));
	vertices->push_back(position + dimensions);
	vertices->push_back(Vector2f(position.x, position.y + dimensions.y));	
	vertices->push_back(position);


	return vertices;
}

Vector2f rotateVec(Vector2f vecIn, float angle) {
	return Vector2f(vecIn.x * cos(angle) - vecIn.y * sin(angle), vecIn.x * sin(angle) + vecIn.y * cos(angle));
}

Vector2f vecSign(Vector2f signOf) {

	return Vector2f(signOf.x > 0 ? 1.0f : signOf.x < 0 ? -1.0f : 0.0f, signOf.y > 0 ? 1.0f : signOf.y < 0 ? -1.0f : 0.0f);
}

Vector2f normGrav(Vector2f vel, Vector2f unitGravity) {
	if (unitGravity.x != 0) {
		float temp = vel.x;
		vel.x = vel.y;
		vel.y = temp;

		temp = unitGravity.x;
		unitGravity.x = unitGravity.y;
		unitGravity.y = temp;
	}
	else {
		if (unitGravity.x < 0) {
			vel.x = -vel.x;
			unitGravity.x = -unitGravity.x;
		}
	}

	if (unitGravity.y < 0) {
		vel.y = -vel.y;
		unitGravity.y = -unitGravity.y;
	}

	return vel;
}

Vector2f normalDivide(Vector2f num, Vector2f den) {
	Vector2f ret;
	if (den.x == 0) {
		den.x = 1;
	}
	ret.x = num.x / den.x;

	if (den.y == 0) {
		den.y = 1;
	}
	ret.y = num.y / den.y;

	return ret;
}

float intervalDistance(Vector2f a, Vector2f b)
{
	if (a.x < b.x) {
		return b.x - a.y;
	}
	else {
		return a.x - b.y;
	}
}

bool lineSide(Vector2f point, Vector2f A, Vector2f B) {
	return (point.x - A.x)*(B.y - A.y) - (point.y - A.y)*(B.x - A.x) < 0;
}

Vector2f abs(Vector2f vec) {
	return Vector2f(abs(vec.x), abs(vec.y));
}

float signedArea(vector<Vector2f> points) {

	float area = 0.0f;
	int j = 1;
	for (int i = 0; i < points.size() - 1; i++, j++) {
		j = j % points.size();
		area += (points[j].x - points[i].x)*(points[j].y + points[i].y);
	}

	area /= 2.0f;

	return area;
}

Vector2f centroid(vector<Vector2f> points) {

	float area = 0.0f;
	float partialArea = 0.0f;
	Vector2f centroid;
	int j = 1;
	for (int i = 0; i < points.size(); i++, j++) {
		j = j % points.size();
		partialArea = (points[i].x*points[j].y - points[j].x*points[i].y);
		area += partialArea;
		centroid += Vector2f(points[j].x + points[i].x, points[j].y + points[i].y) * partialArea;
	}

	area /= 2.0f;

	centroid = centroid / (6.0f * area);

	return centroid;
}