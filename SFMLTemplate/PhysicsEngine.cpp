#include "stdafx.h"
#include "PhysicsEngine.h"

float currentDT;


PhysicsEngine::PhysicsEngine()
{

}


PhysicsEngine::~PhysicsEngine()
{

}

void PhysicsEngine::updatePhysics(float deltaTime, std::vector<std::vector<SpacialPartition*>*>* partitions, std::vector<Entity*>* levelEntities, std::vector<Tile*>* levelTiles) {


	//if (getFPS() < 55) {
	//	cout << "Number of boi " << levelEntities->size() << " with fps " << getFPS() << endl;
	//}


	//cout << "Number of boi " << levelEntities->size() << " with fps " << getFPS() << endl;


	Int64 before = getTimer()->getElapsedTime().asMicroseconds();

	Entitycollisions.clear();
	Tilecollisions.clear();
	
	currentDT = deltaTime;
	
	//Broad Phase
	
	int currentChecks = 0;
	
	for (int i = 0; i < partitions->size(); i++) {
		for (int j = 0; j < partitions->at(0)->size(); j++) {


			std::vector<Entity*>* entities = partitions->at(i)->at(j)->entities;
			if (entities->size() == 0) continue;
			std::vector<Tile*>* tiles = new std::vector<Tile*>();
			for (int k = 0; k < partitionSize; k++) {
				for (int l = 0; l < partitionSize; l++) {
					tiles->push_back(partitions->at(i)->at(j)->tiles[k][l]);
				}
			}

			if (j == 14) {
				//std::cout << i << " " << j << std::endl;
			}

			for (int aa = 0; aa < entities->size(); aa++) {
				for (int bb = 0; bb < tiles->size(); bb++) {
						if (tiles->at(bb) == NULL) {
							continue;
						}



					currentChecks++;
					//float r1 = entities->at(i)->radius;
					//float r2 = tiles->at(j)->radius;

					//if (Distance(entities->at(i)->origin, tiles->at(j)->origin) <= r1 + r2) {
						//bodyPair pair;
					collPair pair;
						//std::cout << "AAA" << std::endl;
						pair.A = (RigidBody*)entities->at(aa);
						//pair.B = (RigidBody*)tiles->at(bb);
						pair.B = tiles->at(bb);
						Tilecollisions.push_back(pair);
					//}
				}
			}

			for (int aaa = 0; aaa < entities->size() - 1; aaa++) {
				for (int bbb = 1; bbb < entities->size(); bbb++) {

					currentChecks++;

					//float r1 = entities->at(i)->radius;
					//float r2 = entities->at(j)->radius;


					//if (Distance(entities->at(i)->origin, entities->at(j)->origin) <= r1 + r2) {
						bodyPair pair;
						pair.A = (RigidBody*)entities->at(aaa);
						pair.B = (RigidBody*)entities->at(bbb);
						Entitycollisions.push_back(pair);
					//}
				}
			}


				//std::cout << "BroadPhaseTime: " << after - before << std::endl;

				//if (Keyboard::isKeyPressed(Keyboard::Num7)) {
				//	std::cout << "BroadPhaseTime: " << after - before << std::endl;
				//	//std::cout << "Time wasted to stupidity: " << wastedTime << std::endl;
				//	//std::cout << "NumPotentialCollisions: " << currentChecks <<  std::endl;
				//	//std::cout << "NumEntityCollision: " << Entitycollisions.size() << " NumTileCollision: " << Tilecollisions.size() << std::endl;
				//}


				//std::cout << "Partition " << i << " Out of " << partitions->size() * partitions->at(0)->size() << std::endl;

		}
	}


	//integrate velocity


	for (auto b : *levelEntities) {
		b->origin += b->velocity;
		b->airTime--;
		if (b->airTime <= 0) {
			b->airTime = 0;
			b->unitGravity.x != 0 ? b->velocity.y *= 0.995f : b->velocity.x *= 0.995f;
		}

		if (abs(b->velocity.x) < 0.0001) {
			b->velocity.x = 0;
		}
		if (abs(b->velocity.y) < 0.0001) {
			b->velocity.y = 0;
		}
	}


	//std::cout << Tilecollisions.size() << std::endl;

	//solve collisions

	for (auto b : Tilecollisions) {
		//if (AABBCollision(&b)) {
		//	resolveCollision(&b);
		//}

		if (tileCollision(&b)) {
			resolveCollision(&b);
		}

	}

	for (auto b : Entitycollisions) {
		if (AABBCollision(&b)) {
			resolveCollision(&b);
		}
	}


	Int64 after = getTimer()->getElapsedTime().asMicroseconds();
	//std::cout << "PhysicsTime: " << after - before << std::endl;

	if (Keyboard::isKeyPressed(Keyboard::Num7)) {
		std::cout << "PhysicsTime: " << after - before << std::endl;
		//std::cout << "Time wasted to stupidity: " << wastedTime << std::endl;
		//std::cout << "NumPotentialCollisions: " << currentChecks <<  std::endl;
		//std::cout << "NumEntityCollision: " << Entitycollisions.size() << " NumTileCollision: " << Tilecollisions.size() << std::endl;
	}

}

//void PhysicsEngine::updatePhysics(float deltaTime, std::vector<Entity*>* entities, std::vector<Tile*>* tiles) {
//	Entitycollisions.clear();
//	Tilecollisions.clear();
//
//	currentDT = deltaTime;
//
//	//Broad Phase
//
//	int currentChecks = 0;
//
//	float before = getTimer()->getElapsedTime().asMicroseconds();
//
//	for (int i = 0; i < entities->size(); i++) {
//		for (int j = 0; j < tiles->size(); j++) {
//			//if (tiles->at(j) == NULL) {
//			//	continue;
//			//}
//
//
//
//			currentChecks++;
//			float r1 = entities->at(i)->radius;	
//			float r2 = tiles->at(j)->radius;
//
//			if (Distance(entities->at(i)->origin, tiles->at(j)->origin) <= r1 + r2) {
//				bodyPair pair;
//				//std::cout << "AAA" << std::endl;
//				pair.A = (RigidBody*)entities->at(i);
//				pair.B = (RigidBody*)tiles->at(j);
//				Tilecollisions.push_back(pair);
//			}
//		}
//	}
//
//	for (int i = 0; i < entities->size() - 1; i++) {
//		for (int j = 1; j < entities->size(); j++) {
//
//			currentChecks++;
//
//			float r1 = entities->at(i)->radius;
//			float r2 = entities->at(j)->radius;
//
//
//			if (Distance(entities->at(i)->origin, entities->at(j)->origin) <= r1 + r2) {
//				bodyPair pair;
//				pair.A = (RigidBody*)entities->at(i);
//				pair.B = (RigidBody*)entities->at(j);
//				Entitycollisions.push_back(pair);
//			}
//		}
//	}
//	
//
//	float after = getTimer()->getElapsedTime().asMicroseconds();
//
//	//std::cout << "BroadPhaseTime: " << after - before << std::endl;
//
//	if (Keyboard::isKeyPressed(Keyboard::Num7)) {
//		std::cout << "BroadPhaseTime: " << after - before << std::endl;
//		//std::cout << "Time wasted to stupidity: " << wastedTime << std::endl;
//		//std::cout << "NumPotentialCollisions: " << currentChecks <<  std::endl;
//		//std::cout << "NumEntityCollision: " << Entitycollisions.size() << " NumTileCollision: " << Tilecollisions.size() << std::endl;
//	}
//
//	//integrate velocity
//
//	for (auto b : *entities) {
//		b->velocity += b->force;
//		b->origin += b->velocity;
//		b->airTime--;
//		if (b->airTime <= 0) {
//			b->airTime = 0;
//			bool force = b->unitGravity.x != 0 ? b->force.y == 0 : b->force.x == 0;
//			if (force) {
//				b->unitGravity.x != 0 ? b->velocity.y *= 0.995 : b->velocity.x *= 0.995;
//			}
//		}
//
//		if (abs(b->velocity.x) < 0.0001) {
//			b->velocity.x = 0;
//		}
//		if (abs(b->velocity.y) < 0.0001) {
//			b->velocity.y = 0;
//		}
//	}
//
//
//	//solve collisions
//
//	for (auto b : Tilecollisions) {
//		if (AABBCollision(&b)) {
//			resolveCollision(&b);
//		}
//	}
//
//	for (auto b : Entitycollisions) {
//		if (AABBCollision(&b)) {
//			resolveCollision(&b);
//		}
//	}
//
//	for (auto b : *entities) {
//		b->force = Vector2f(0, 0);
//		b->shouldJump = false;
//	}
//
//	for (auto b : *tiles) {
//		if (b == NULL) continue;
//		b->force = Vector2f(0, 0);
//		b->shouldJump = false;
//	}
//	
//}

std::vector<Entity*> PhysicsEngine::queryAABB(FloatRect query, std::vector<Entity*>* entities) {

	std::vector<Entity*> results;

	for (auto e : *entities) {
		sf::FloatRect body(e->origin - e->dimensions / 2.0f, e->dimensions);
		if (query.intersects(body)) {
			results.push_back(e);
		}
	}

	return results;
}


bool PhysicsEngine::queryPlayerAABB(FloatRect query, Player* player) {
	sf::FloatRect body(player->origin - player->dimensions / 2.0f, player->dimensions);
	if (query.intersects(body)) return true;
	return false;
}


bool AABBCollision(bodyPair* pair) {

	RigidBody* A = pair->A;
	RigidBody* B = pair->B;

	Vector2f minA = A->origin - A->dimensions / 2.0f;
	Vector2f minB = B->origin - B->dimensions / 2.0f;

	Vector2f maxA = A->origin + A->dimensions / 2.0f;
	Vector2f maxB = B->origin + B->dimensions / 2.0f;

	Vector2f centerA = A->origin;
	Vector2f centerB = B->origin;

	Vector2f distance = Vector2f(centerB.x - centerA.x, centerB.y - centerA.y);

	// Calculate half extents along x axis for each object
	float a_extent = (maxA.x - minA.x) / 2;
	float b_extent = (maxB.x - minB.x) / 2;

	// Calculate overlap on x axis
	float x_overlap = a_extent + b_extent - abs(distance.x);

	// SAT test on x axis
	if (x_overlap > 0)
	{
		// Calculate half extents along y axis for each object
		float a_extent = (maxA.y - minA.y) / 2;
		float b_extent = (maxB.y - minB.y) / 2;

		// Calculate overlap on y axis
		float y_overlap = a_extent + b_extent - abs(distance.y);

		// SAT test on y axis
		if (y_overlap > 0)
		{

			//AABB's have collided

			// Find out which axis is axis of least penetration
			if (x_overlap < y_overlap)
			{
				// Point towards B knowing that n points from A to B
				if (distance.x < 0) {
					pair->normal = Vector2f(1, 0);
				}
				else {
					pair->normal = Vector2f(-1, 0);
				}

				pair->penetration = x_overlap;


			}
			else {
				// Point toward B knowing that n points from A to B
				if (distance.y < 0) {
					pair->normal = Vector2f(0, 1);
				}
				else {
					pair->normal = Vector2f(0, -1);
				}

				pair->penetration = y_overlap;
			}

			return true;

		}

	}

	return false;
}



bool PhysicsEngine::tileCollision(collPair* pair) {

	RigidBody* A = pair->A;
	RigidBody* B = pair->B;

	Vector2f minA = A->origin - A->dimensions / 2.0f;
	Vector2f minB = B->origin - B->dimensions / 2.0f;

	Vector2f maxA = A->origin + A->dimensions / 2.0f;
	Vector2f maxB = B->origin + B->dimensions / 2.0f;

	Vector2f centerA = A->origin;
	Vector2f centerB = B->origin;

	Vector2f distance = Vector2f(centerB.x - centerA.x, centerB.y - centerA.y);

	// Calculate half extents along x axis for each object
	float a_extent = (maxA.x - minA.x) / 2;
	float b_extent = (maxB.x - minB.x) / 2;

	// Calculate overlap on x axis
	float x_overlap = a_extent + b_extent - abs(distance.x);

	// SAT test on x axis
	if (x_overlap > 0)
	{
		// Calculate half extents along y axis for each object
		float a_extent = (maxA.y - minA.y) / 2;
		float b_extent = (maxB.y - minB.y) / 2;

		// Calculate overlap on y axis
		float y_overlap = a_extent + b_extent - abs(distance.y);

		// SAT test on y axis
		if (y_overlap > 0)
		{

			//AABB's have collided

			for (auto vec : pair->B->correctNormals) {
				Vector2f leastPen(vec.x * x_overlap, vec.y * y_overlap);

				if (vec.x != 0) {
					if (pair->penetration == 0) {
						if (signbit(leastPen.x) != signbit(distance.x)) {
							pair->penetration = abs(leastPen.x);
							pair->normal = vec;
						}
					}

					if (magnitude(leastPen) < pair->penetration&&signbit(leastPen.x) != signbit(distance.x)) {
						pair->penetration = abs(leastPen.x);
						pair->normal = vec;
					}
				}
				else {
					if (pair->penetration == 0) {
						if (signbit(leastPen.y) != signbit(distance.y)) {
							pair->penetration = abs(leastPen.y);
							pair->normal = vec;
						}
					}

					if (magnitude(leastPen) < pair->penetration&&signbit(leastPen.y) != signbit(distance.y)) {
						pair->penetration = abs(leastPen.y);
						pair->normal = vec;
					}
				}
			}








			//// Find out which axis is axis of least penetration
			//if (x_overlap < y_overlap)
			//{
			//	// Point towards B knowing that n points from A to B
			//	if (distance.x < 0) {
			//		pair->normal = Vector2f(1, 0);
			//	}
			//	else {
			//		pair->normal = Vector2f(-1, 0);
			//	}

			//	pair->penetration = x_overlap;

			//	if (find(pair->B->correctNormals.begin(), pair->B->correctNormals.end(), pair->normal) == pair->B->correctNormals.end()) {
			//		if (find(pair->B->correctNormals.begin(), pair->B->correctNormals.end(), Vector2f(0, -1) * (float)signbit(distance.y)) != pair->B->correctNormals.end()) {
			//			pair->normal = Vector2f(0, -1) * (float)signbit(distance.y);

			//			cout << pair->normal.x << " " << pair->normal.y << endl;

			//			pair->penetration = y_overlap;
			//		}
			//	}


			//}
			//else {
			//	// Point toward B knowing that n points from A to B
			//	if (distance.y < 0) {
			//		pair->normal = Vector2f(0, 1);
			//	}
			//	else {
			//		pair->normal = Vector2f(0, -1);
			//	}

			//	pair->penetration = y_overlap;


			//	if (find(pair->B->correctNormals.begin(), pair->B->correctNormals.end(), pair->normal) == pair->B->correctNormals.end()) {
			//		if (find(pair->B->correctNormals.begin(), pair->B->correctNormals.end(), Vector2f(-1, 0) * (float)signbit(distance.x)) != pair->B->correctNormals.end()) {
			//			pair->normal = Vector2f(-1, 0) * (float)signbit(distance.x);

			//			cout << pair->normal.x << " " << pair->normal.y << endl;

			//			pair->penetration = x_overlap;
			//		}
			//	}

			//}






			if (magnitude(pair->normal) == 0 || pair->penetration == 0) {
				cout << "wtf" << endl;

				if (x_overlap < y_overlap)
				{
					if (distance.x < 0) {
						pair->normal = Vector2f(1, 0);
					}
					else {
						pair->normal = Vector2f(-1, 0);
					}

					pair->penetration = x_overlap;


				}
				else {
					if (distance.y < 0) {
						pair->normal = Vector2f(0, 1);
					}
					else {
						pair->normal = Vector2f(0, -1);
					}

					pair->penetration = y_overlap;
				}

			}

			return true;

		}

	}

	return false;
}



void resolveCollision(bodyPair* pair) {
	RigidBody* A = pair->A;
	RigidBody* B = pair->B;

	if (A->unitGravity.x == 0 && pair->normal.x == 0 || A->unitGravity.y == 0 && pair->normal.y == 0) {

		//Reletive Horizontal Collision

	}
	else {

		//Reletive Vertical Collision

		if (pair->penetration < 1) {
			return;
		}

	}

	// Calculate relative velocity
	Vector2f reletiveVelocity = B->velocity - A->velocity;


	// Calculate relative velocity in terms of the normal direction
	float velAlongNormal = dotProduct(reletiveVelocity, pair->normal);

	// Do not resolve if velocities are separating
	if (-velAlongNormal > 0) //should be  a >, but works with < (vel should be positive)
		return;

	// Calculate restitution
	float e = std::min(A->restitution, B->restitution);

	// Calculate impulse scalar
	float j = -(1 + A->restitution) * velAlongNormal;
	float i = -(1 + B->restitution) * velAlongNormal;
	j /= A->massInv + B->massInv;
	i /= A->massInv + B->massInv;

	// Apply impulse
	Vector2f impulse(j * pair->normal.x, j * pair->normal.y);
	Vector2f impulseb(i * pair->normal.x, i * pair->normal.y);

	A->velocity -= A->massInv * impulse;
	B->velocity += B->massInv * impulseb;

	positionalCorrection(pair);

	if (A->unitGravity == -pair->normal) {
		A->airTime = 16;
	}

	if (B->unitGravity == -pair->normal) {
		B->airTime = 16;
	}


	//FRICTION LOL
	//float friction = 0.4f;

	if (pair->penetration == 0) {
		cout << pair->penetration << endl;
	}

	float friction = 0.9f;
	Vector2f frictionVec = friction * Vector2f(-pair->normal.y, pair->normal.x);
	pair->A->friction = frictionVec;

	//if (A->unitGravity == -pair->normal) { //friction

	//	A->airTime = 16;

	//	if (A->unitGravity.y == 0) {
	//		if (A->force.y == 0 || signbit(A->force.y) != signbit(A->velocity.y)) {
	//			A->velocity.y *= 0.9;
	//		}
	//	}
	//	else {
	//		if (A->force.x == 0 || signbit(A->force.x) != signbit(A->velocity.x)) {
	//			A->velocity.x *= 0.9;
	//		}
	//	}
	//}


	//float angle;

	//if (A->unitGravity.x == 0) {
	//	angle = asin(A->unitGravity.y);
	//}
	//else {
	//	angle = acos(A->unitGravity.x);
	//}

	//if (A->shouldJump && pair->normal == -A->unitGravity) {
	//	A->velocity -= 7.0f * Vector2f(cos(angle), sin(angle));
	//}

}


void resolveCollision(collPair* pair) {
	RigidBody* A = pair->A;
	RigidBody* B = (RigidBody*)pair->B;
	Vector2f reletiveVelocity = B->velocity - A->velocity;
	float velAlongNormal = dotProduct(reletiveVelocity, pair->normal);

	if (-velAlongNormal > 0) return;

	float e = std::min(A->restitution, B->restitution);
	float j = -(1 + A->restitution) * velAlongNormal;
	float i = -(1 + B->restitution) * velAlongNormal;
	j /= A->massInv + B->massInv;
	i /= A->massInv + B->massInv;
	Vector2f impulse(j * pair->normal.x, j * pair->normal.y);
	Vector2f impulseb(i * pair->normal.x, i * pair->normal.y);

	A->velocity -= A->massInv * impulse;
	B->velocity += B->massInv * impulseb;
	positionalCorrection(pair);

	if (A->unitGravity == -pair->normal) {
		A->airTime = 16;
	}

	if (B->unitGravity == -pair->normal) {
		B->airTime = 16;
	}


	//FRICTION LOL
	if (pair->penetration == 0) {
		cout << pair->penetration << endl;
	}

	//this affects how quickly the player goes from moving to stationary when no buttons are held on the ground
	float friction = mean(A->dynamicFriction, B->dynamicFriction);
	Vector2f frictionVec = friction * Vector2f(-pair->normal.y, pair->normal.x);
	pair->A->friction = frictionVec;
}


void positionalCorrection(bodyPair* pair) {
	RigidBody* A = pair->A;
	RigidBody* B = pair->B;
	const float percent = 0.8f; // usually 20% to 80%
	const float slop = 0.01f;// usually 0.01 to 0.1
	float correctionFloat = std::max(pair->penetration - slop, 0.0f) / (A->massInv + B->massInv);
	Vector2f correction = correctionFloat * pair->normal;
	A->origin += A->massInv * correction;
	B->origin -= B->massInv * correction;
}

void positionalCorrection(collPair* pair) {
	bodyPair newPair;
	newPair.A = pair->A;
	newPair.B = (RigidBody*)pair->B;
	newPair.normal = pair->normal;
	newPair.penetration = pair->penetration;
	positionalCorrection(&newPair);
}


