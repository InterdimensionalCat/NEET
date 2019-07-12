#include "stdafx.h"
#include "Terrain.h"


Terrain::Terrain(vector<Vector2f> points, Vector2f position, Vector2f dimensions, Scene* master, float rotation) : GameObject(master)
{
	addComponent(new PolygonSprite(Color::Red));
	RigidBody* body = new RigidBody("ground");
	addComponent(body);
	transform->changeShape(points, position, dimensions, rotation);
	init();
	body->setGravity(false);
	body->calcInertia(transform, 1.0f, true);
}

Terrain::Terrain(Vector2f position, Vector2f dimensions, Scene* master, float rotation) : GameObject(master)
{
	vector<Vector2f> points = { Vector2f(0,0),Vector2f(1,0), Vector2f(1,1), Vector2f(0,1) };
	Terrain(points, position, dimensions, master, rotation);
}


Terrain::~Terrain()
{
}
