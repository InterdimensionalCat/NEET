#pragma once
#include "stdafx.h"


//self explanitory; adds vector math functions that SFML lacks
//as SFML for some reason includes vectors but no vector math


using namespace sf;
using namespace std;

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