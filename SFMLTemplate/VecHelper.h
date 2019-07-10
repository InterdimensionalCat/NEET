#pragma once
#include "stdafx.h"

using namespace sf;
using namespace std;

//self explanitory; adds vector math functions that SFML lacks
//as SFML for some reason includes vectors but no vector math

//2x2 matrix in this form
// | x.x, x.y |
// | y.x, y.y |

struct matrix {

	Vector2f x;
	Vector2f y;

	matrix(Vector2f x, Vector2f y) {
		matrix::x = x;
		matrix::y = y;
	}

	matrix(float radian) {
		float cos = std::cos(radian);
		float sin = std::sin(radian);
		x = Vector2f(cos, -sin);
		y = Vector2f(sin, cos);
	}

	matrix() {
		matrix(0.0f);
	}

	//rotate a vector
	const Vector2f operator*(const Vector2f& vec) const
	{
		return Vector2f(x.x * vec.x + x.y * vec.y, y.x * vec.x + y.y * vec.y);
	}
};

Vector2f x;
Vector2f y;

float Distance(Vector2f a, Vector2f b);
float dotProduct(Vector2f a, Vector2f b);
float magnitude(Vector2f vecIn);
float Average(float a, float b);
float mean(float a, float b);

Vector2f normalize(Vector2f vecIn);
Vector2f CrossProduct(const Vector2f& a, float s);
Vector2f CrossProduct(float s, const Vector2f& a);
float CrossProduct(const Vector2f& a, const Vector2f& b);

std::vector<sf::Vector2f>* createPoly(sf::Vector2f position, sf::Vector2f dimensions);
Vector2f rotateVec(Vector2f vecIn, float angle);

Vector2f vecSign(Vector2f signOf);
Vector2f normGrav(Vector2f vel, Vector2f unitGravity);
Vector2f normalDivide(Vector2f num, Vector2f den);


bool lineSide(Vector2f point, Vector2f A, Vector2f B);
float intervalDistance(Vector2f a, Vector2f b);

Vector2f abs(Vector2f vec);
float signedArea(vector<Vector2f> points);
Vector2f centroid(vector<Vector2f> points);