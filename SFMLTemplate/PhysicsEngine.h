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
	Vector2f contacts[2];
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
	bool enhancedSAT(collision* pair);
	void resolveCollision(collision* pair);
	void positionalCorrection(collision* pair);
	void applyFriction(collision* pair, float j);
	void generateCollisions(); // BRUTE FORCE
	void integrateVelocity(float deltaTime);
	vector<Vector2f> collisionPoints(collision* pair);
	pair<Vector2f, Vector2f> findFeature(polygon polygon, Vector2f normal);
	vector<Vector2f> clip(Vector2f min, Vector2f max, Vector2f normal, float offset);
	float FindAxisLeastPenetration(int *faceIndex, collision* pair);
	bool biasGreaterThan(float a, float b);
	void FindIncidentFace(Vector2f *v, polygon* RefPoly, polygon* IncPoly, int referenceIndex);
	Scene* masterScene;
	vector<RigidBody*> bodies;
	vector<collision> collisions;
};
