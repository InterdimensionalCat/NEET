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

	material() {
		material::mass = 0.0f;
		material::restitution = 0.0f;
		material::staticFriction = 0.0f;
		material::dynamicFriction = 0.0f;
	}

	float restitution;
	float mass;
	float staticFriction;
	float dynamicFriction;
};

class RigidBody : public Component
{
public:
	RigidBody(string material);
	~RigidBody();

	material mat;
};

material generateMaterial(string name) {
	if (name == "test") {
		return material(10.0f, 0.9f, 0.9f, 0.4f);
	}

	return material(10.0f, 0.9f, 0.9f, 0.4f);
}

