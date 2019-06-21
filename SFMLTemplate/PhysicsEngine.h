#pragma once
#include "stdafx.h"
#include "RigidBody.h"

class RigidBody;

struct collision
{
public:
	collision(RigidBody* A, RigidBody* B) {
		collision::A = A;
		collision::B = B;
	}
	RigidBody* A;
	RigidBody* B;
	Vector2f normal;
	float penetration;
};


class PhysicsEngine
{
public:
	PhysicsEngine(Scene* master);
	~PhysicsEngine();
	void addBody(RigidBody* body);
	void step(float deltaTime);
	void broadPhase();
	void applyGravity();
	bool SAT(collision* pair);
	void resolveCollision(collision* pair);
	void positionalCorrection(collision* pair);
	void generateCollisions(); // BRUTE FORCE
	Scene* masterScene;
	vector<RigidBody*> bodies;
	vector<collision> collisions;
};
