#pragma once
#include "stdafx.h"


struct material {
public:
	material(float restitution, float mass, float staticFriction, float dynamicFriction) {
		material::mass = mass;
		material::restitution = restitution;
		material::staticFriction = staticFriction;
		material::dynamicFriction = dynamicFriction;
		if (mass == 0) {
			massInv = 0; //infinite mass
		} else {
			massInv = 1 / mass;
		}
	}

	material() {
		material(0.0f, 0.0f, 0.0f, 0.0f);
	}

	float restitution;
	float mass;
	float staticFriction;
	float dynamicFriction;
	float massInv;
};

class RigidBody : public Component
{
public:
	RigidBody(string material);
	~RigidBody();
	void setGravity(bool grav) {
		gravity = grav;
	}

	void onUpdate(float deltaTime, GameMouse* mouse, GameKeyboard* keyboard);
	void init();

	bool gravity;
	Vector2f velocity;
	material mat;

	material generateMaterial(string name) {
		if (name == "test") {
			return material(0.9f, 10.0f, 0.9f, 0.4f);
		}

		return material();
	}
};

