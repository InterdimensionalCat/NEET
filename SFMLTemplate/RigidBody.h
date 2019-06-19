#pragma once
#include "stdafx.h"


struct material {
public:
	material(float restitution, float mass, float staticFriction, float dynamicFriction) {
		material::mass = mass;
		material::restitution = restitution;
		material::staticFriction = staticFriction;
		material::dynamicFriction = dynamicFriction;
	}
	float restitution;
	float mass;
	float staticFriction;
	float dynamicFriction;
};

class RigidBody : Component
{
public:
	RigidBody(string material);
	~RigidBody();

	material mat
};

material generateMaterial(string name) {
	if (name == "test") {
		return material(10, 0.9, 0.9, 0.4);
	}

	return material(10, 0.9, 0.9, 0.4);
}

