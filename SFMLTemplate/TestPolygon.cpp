#include "stdafx.h"
#include "TestPolygon.h"


TestPolygon::TestPolygon(Vector2f position, polygon body, Scene* master, string material) : GameObject(master)
{
	addComponent(new PolygonSprite(Color::Red));
	addComponent(new RigidBody(material));
	transform->move(position);
	transform->changeShape(body.points);
	//addComponent(transform);
	init();

}


TestPolygon::~TestPolygon()
{

}
