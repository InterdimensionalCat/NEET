#include "stdafx.h"
#include "TestPolygon.h"


TestPolygon::TestPolygon(Vector2f position, polygon body, Scene* master, string material) : GameObject(master)
{
	addComponent(new PolygonSprite(Color::Red));
	addComponent(new RigidBody(material));
	transform->changeShape(body.points, position);
	//transform->move(position);
	//addComponent(transform);
	init();

}


TestPolygon::~TestPolygon()
{

}
