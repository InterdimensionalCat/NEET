#include "stdafx.h"
#include "PhysicsEngine.h"

float currentDT;
Vector2f gravity(0.0f, -0.5f);


PhysicsEngine::PhysicsEngine(Scene* master)
{
	masterScene = master;
}


PhysicsEngine::~PhysicsEngine()
{

}

void PhysicsEngine::addBody(RigidBody* body) {
	bodies.push_back(body);
}

void PhysicsEngine::generateCollisions() {
	for (auto body1 : bodies) {
		for (auto body2 : bodies) {
			if (body1 == body2) continue;
			collisions.push_back(collision(body1, body2));
		}
	}
}

void PhysicsEngine::applyGravity() {
	for (auto body : bodies) {
		if (body->gravity) {
			body->velocity -= gravity;
		}
	}
}

void PhysicsEngine::step(float deltaTime) {

	currentDT = deltaTime;
	collisions.clear();

	//Broad Phase


	generateCollisions();


	//integrate velocity

	applyGravity();

	for (auto body : bodies) {
		TransformComp* trans = body->masterObj->transform;
		trans->move(body->velocity);
	}

	//resolve collisisons

	for (auto collision : collisions) {
		if (SAT(&collision)) {

			cout << "Collision occurs" << endl;

			resolveCollision(&collision);
		}
	}


}


bool PhysicsEngine::SAT(collision* pair) {

	polygon A = pair->A->masterObj->transform->shape;
	polygon B = pair->B->masterObj->transform->shape;
	vector<Vector2f> Anormals = A.normals;
	vector<Vector2f> Bnormals = B.normals;

	//project both polygons onto all normals (of the terrain)

	for (unsigned int i = 0; i < Anormals.size(); i++) {
		Vector2f axis = Anormals[i];

		Vector2f ARange = A.projectPolygon(axis);
		Vector2f BRange = B.projectPolygon(axis);

		//note that penetration will be negative if the shapes overlap

		float penetration = intervalDistance(ARange, BRange);
		if (penetration > 0) {
			return false; //early out
		}
		if (penetration > pair->penetration) {
			pair->penetration = penetration;
			pair->normal = axis;
		}
	}

	for (unsigned int i = 0; i < Bnormals.size(); i++) {
		Vector2f axis = Bnormals[i];

		Vector2f ARange = A.projectPolygon(axis);
		Vector2f BRange = B.projectPolygon(axis);

		//note that penetration will be negative if the shapes overlap

		float penetration = intervalDistance(ARange, BRange);
		if (penetration > 0) {
			return false; //early out
		}
		if (penetration > pair->penetration) {
			pair->penetration = penetration;
			pair->normal = axis;
		}
	}

	pair->penetration *= -1.0f;

	return true;
}


void PhysicsEngine::resolveCollision(collision* pair) {
	RigidBody* A = pair->A;
	RigidBody* B = pair->B;

	// Calculate relative velocity
	Vector2f reletiveVelocity = B->velocity - A->velocity;


	// Calculate relative velocity in terms of the normal direction
	float velAlongNormal = dotProduct(reletiveVelocity, pair->normal);

	// Do not resolve if velocities are separating
	if (-velAlongNormal > 0) //should be  a >, but works with < (vel should be positive)
		return;

	// Calculate restitution
	float e = std::min(A->mat.restitution, B->mat.restitution);

	// Calculate impulse scalar
	float j = -(1 + A->mat.restitution) * velAlongNormal;
	//float i = -(1 + B->mat.restitution) * velAlongNormal;
	j /= A->mat.massInv + B->mat.massInv;
	//i /= A->mat.massInv + B->mat.massInv;

	// Apply impulse
	Vector2f impulse(j * pair->normal.x, j * pair->normal.y);
	//Vector2f impulseb(i * pair->normal.x, i * pair->normal.y);

	A->velocity -= A->mat.massInv * impulse;
	B->velocity += B->mat.massInv * impulse;

	//positionalCorrection(pair);

	return;
}
//
//
void PhysicsEngine::positionalCorrection(collision* pair) {
	RigidBody* A = pair->A;
	RigidBody* B = pair->B;
	const float percent = 0.8f; // usually 20% to 80%
	const float slop = 0.01f;// usually 0.01 to 0.1
	float correctionFloat = std::max(pair->penetration - slop, 0.0f) / (A->mat.massInv + B->mat.massInv);
	Vector2f correction = correctionFloat * pair->normal;
	A->masterObj->transform->move(A->mat.massInv * correction);
	B->masterObj->transform->move(A->mat.massInv * correction);
}
//
//void positionalCorrection(collPair* pair) {
//	bodyPair newPair;
//	newPair.A = pair->A;
//	newPair.B = (RigidBody*)pair->B;
//	newPair.normal = pair->normal;
//	newPair.penetration = pair->penetration;
//	positionalCorrection(&newPair);
//}
