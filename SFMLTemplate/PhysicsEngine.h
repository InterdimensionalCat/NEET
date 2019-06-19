#pragma once
#include "stdafx.h"
#include "Entity.h"
#include "RigidBody.h"
#include "Player.h"
#include "Tile.h"
#include "SpacialPartition.h"

using namespace sf;

class bodyPair
{
public:
	RigidBody* A;
	RigidBody* B;
	Vector2f normal;
	float penetration;
};

struct collPair {

	RigidBody* A;
	Tile* B;

	float penetration = 0;
	Vector2f normal = Vector2f(0, 0);
	vector<Vector2f>* pushVectors;
};

class PhysicsEngine
{
public:
	PhysicsEngine();
	~PhysicsEngine();
	vector<Entity*> queryAABB(FloatRect query, std::vector<Entity*>* entities);
	bool queryPlayerAABB(FloatRect query, Player* player);
	void updatePhysics(float deltaTime, std::vector<std::vector<SpacialPartition*>*>* partitions, std::vector<Entity*>* levelEntities, std::vector<Tile*>* levelTiles);
	vector<bodyPair> Entitycollisions;
	vector<collPair> Tilecollisions;

	bool tileCollision(collPair* pair);

};


void positionalCorrection(bodyPair* pair);
void resolveCollision(bodyPair* pair);
bool AABBCollision(bodyPair* pair);

void resolveCollision(collPair* pair);
void positionalCorrection(collPair* pair);
