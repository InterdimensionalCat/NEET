#pragma once
#include "stdafx.h"


struct material {
public:
	material(float restitution, float mass, float staticFriction, float dynamicFriction, float gravityScale, float inertia) {
		material::mass = mass;
		material::restitution = restitution;
		material::staticFriction = staticFriction;
		material::dynamicFriction = dynamicFriction;
		material::gravityScale = gravityScale;
		material::inertia = inertia;
		if (mass == 0) {
			massInv = 0; //infinite mass
		} else {
			massInv = 1 / mass;
		}

		if (inertia == 0) {
			inertInv = 0; //does not rotate
		}
		else {
			inertInv = 1 / inertia;
		}
	}

	material() {
		material(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	}

	float restitution;
	float mass;
	float staticFriction;
	float dynamicFriction;
	float massInv;
	float gravityScale;
	float inertia;
	float inertInv;
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
	Vector2f force;
	material mat;

	//rotational

	float orientation;// radians
	float angularVelocity;
	float torque;

	material generateMaterial(string name) {
		if (name == "test") {
			return material(0.3f, 1.0f, 0.9f, 0.4f, 0.25, 1.0f);
		}

		if (name == "ground") {
			return material(0.1f, 0.0f, 0.9f, 0.9f, 0.25, 1.0f);
		}

		if (name == "player") {
			return material(0.9f, 100.0f, 0.9f, 0.9f, 0.25, 10.f);
		}

		return material();
	}
};

