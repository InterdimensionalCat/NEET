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

	//cull dupes

	for (int i = 0; i < collisions.size() - 1; i++) {
		for (int j = 1; j < collisions.size(); j++) {
			if (collisions[i].A == collisions[j].B && collisions[i].B == collisions[j].A) {
				collisions.erase(collisions.begin() + i);
				//i--;
				//j--;
			}
		}
	}

	if (collisions[0].A == collisions[collisions.size() - 1].B && collisions[0].B == collisions[collisions.size() - 1].A) {
		collisions.erase(collisions.begin() + 0);
	}

	for (int i = 0; i < collisions.size(); i++) {
		if (collisions[i].A->mat.mass == 0 && collisions[i].B->mat.mass == 0) {
			collisions.erase(collisions.begin() + i);
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
		else if (penetration == pair->penetration) {
			Vector2f reletiveVelocity = pair->B->velocity - pair->A->velocity;
			float vel1 = dotProduct(reletiveVelocity, pair->normal);
			float vel2 = dotProduct(reletiveVelocity, axis);
			if (vel2 < vel1) {
				pair->penetration = penetration;
				pair->normal = axis;
			}

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
		else if (penetration == pair->penetration) {
			Vector2f reletiveVelocity = pair->B->velocity - pair->A->velocity;
			float vel1 = dotProduct(reletiveVelocity, pair->normal);
			float vel2 = dotProduct(reletiveVelocity, axis);
			if (vel2 < vel1) {
				pair->penetration = penetration;
				pair->normal = axis;
			}

		}
	}

	//pair->penetration -= 0.05f;

	return true;
}


void PhysicsEngine::resolveCollision(collision* pair) {
	RigidBody* A = pair->A;
	RigidBody* B = pair->B;

	//Vector2f imp = pair->normal * pair->penetration;

	//if (A->mat.massInv != 0) {
	//	A->velocity = imp;
	//}

	//if (B->mat.massInv != 0) {
	//	B->velocity = -imp;
	//}

	//cout << B->velocity.y << endl;

	//return;

	// Calculate relative velocity
	Vector2f reletiveVelocity = B->velocity - A->velocity;


	// Calculate relative velocity in terms of the normal direction
	float velAlongNormal = dotProduct(reletiveVelocity, pair->normal);

	// Do not resolve if velocities are separating
	if (velAlongNormal > 0) //should be  a >, but works with < (vel should be positive)
		return;

	// Calculate restitution
	float e = std::min(A->mat.restitution, B->mat.restitution);

	// Calculate impulse scalar
	float j = -(1 + e) * velAlongNormal;
	j /= (A->mat.massInv + B->mat.massInv);

	// Apply impulse
	Vector2f impulse = pair->normal * j;

	A->velocity -= A->mat.massInv * impulse;
	B->velocity += B->mat.massInv * impulse;

	positionalCorrection(pair);

	//cout << pair->penetration << endl;
	//cout << B->mat.massInv * impulse.x << " " << B->mat.massInv * impulse.y << endl;

	return;
}


void PhysicsEngine::positionalCorrection(collision* pair) {
	RigidBody* A = pair->A;
	RigidBody* B = pair->B;
	const float percent = 1.0f; // usually 20% to 80%
	const float slop = 0.00f;// usually 0.01 to 0.1
	float correctionFloat = std::max(-pair->penetration - slop, 0.0f) / (A->mat.massInv + B->mat.massInv) * percent;
	Vector2f correction = correctionFloat * pair->normal;
	A->masterObj->transform->move(-A->mat.massInv * correction);
	B->masterObj->transform->move(B->mat.massInv * correction);
}
