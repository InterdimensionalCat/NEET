#include "stdafx.h"
#include "ControlPoly.h"


ControlPoly::ControlPoly(Vector2f position, Scene* master) : GameObject(master)
{
	addComponent(new PolygonSprite(Color::Blue));
	RigidBody* body = new RigidBody("player");
	addComponent(body);
	addComponent(new Controller());
	transform->changeShape(position, Vector2f(64, 64));
	init();
	body->calcInertia(transform, 1.0, false);


}


ControlPoly::~ControlPoly()
{

}
