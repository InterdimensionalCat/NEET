#pragma once
#include "stdafx.h"

//Class for a standard physical body within the game
//Mass, volume, and area are assumed constant for each rigid body
//Currently, ALL rigid bodies have a polygonal body with a square bounding box
//constructor position is top left corner, origin is center
//Also note that constructor is passed local polygon points, which are then converted to gloabl coordinates

class Polygon;

class RigidBody
{
public:
	RigidBody(Vector2f position, Vector2f dimensions, float restitution, float mass, float staticFriction, float dynamicFriction);
	~RigidBody();
	FloatRect getBounds();
	void onCollision();
	void rotate(Vector2f unitGravity);
	void rotate(bool side); // true is right (->), false is left (<-)

	Vector2f origin;
	Vector2f dimensions;
	//Vector2f force;
	Vector2f velocity;
	Vector2f friction;
	Vector2f unitGravity; //the direction that gravity should act on this object
	float massInv; //note that inverse mass is calculated upon construction and then stored, the actual mass is not stored
	float restitution; //"bounciness"
	float staticFriction;
	float dynamicFriction;
	//bool shouldJump;
	bool flip;
	int airTime;
	//int jumpTime;
};

