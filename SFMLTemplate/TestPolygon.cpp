#include "stdafx.h"
#include "TestPolygon.h"


TestPolygon::TestPolygon(Vector2f position, polygon body, Scene* master) : GameObject(master)
{
	addComponent(new PolygonSprite(Color::Red));
	addComponent(new RigidBody("test"));
	transform->move(position);
	transform->changeShape(body.points);
	//addComponent(transform);
	init();

}


TestPolygon::~TestPolygon()
{

}
