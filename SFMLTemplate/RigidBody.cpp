#include "stdafx.h"
#include "RigidBody.h"


RigidBody::RigidBody(sf::Vector2f position, sf::Vector2f dimensions, float restitution, float mass, float staticFriction, float dynamicFriction)
{
	velocity = sf::Vector2f(0,0);
	origin = sf::Vector2f(position.x + dimensions.x / 2, position.y + dimensions.y / 2);
	unitGravity = Vector2f(0, 1);
	origin = position + dimensions / 2.0f;
	RigidBody::dimensions = dimensions;
	RigidBody::restitution = restitution;
	RigidBody::staticFriction = staticFriction;
	RigidBody::dynamicFriction = dynamicFriction;
	if (mass == 0) {
		massInv = 0; //infinite mass object
	} else {
		massInv = 1 / mass;
	}
}

RigidBody::~RigidBody()
{

}

FloatRect RigidBody::getBounds() {
	return FloatRect(Vector2f(origin - dimensions / 2.0f), dimensions);
}

void RigidBody::onCollision() {

}

void RigidBody::rotate(Vector2f unitGravity) {
	if (abs(unitGravity.x) != abs(RigidBody::unitGravity.x)) {
		dimensions = Vector2f(dimensions.y, dimensions.x);
	}
	RigidBody::unitGravity = unitGravity;
	velocity = Vector2f(0, 0);
}

void RigidBody::rotate(bool side) {
	float angle;

	if (unitGravity.x == 0) {
		angle = asin(unitGravity.y);
	}
	else {
		angle = acos(unitGravity.x);
	}

	if (side) {
		unitGravity = Vector2f(cos(angle - 3.14159265f / 2), sin(angle - 3.14159265f / 2));
	}
	else {
		unitGravity = Vector2f(cos(angle + 3.14159265f / 2), sin(angle + 3.14159265f / 2));
	}

	if (abs(unitGravity.x) < 0.5) {
		unitGravity.x = 0;
	}

	if (abs(unitGravity.y) < 0.5) {
		unitGravity.y = 0;
	}

	dimensions = Vector2f(dimensions.y, dimensions.x);
	velocity = Vector2f(0, 0);
}