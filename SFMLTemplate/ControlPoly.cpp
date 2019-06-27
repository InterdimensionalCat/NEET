#include "stdafx.h"
#include "ControlPoly.h"


ControlPoly::ControlPoly(Vector2f position, Scene* master) : GameObject(master)
{
	addComponent(new PolygonSprite(Color::Blue));
	addComponent(new RigidBody("player"));
	addComponent(new Controller());
	transform->changeShape(position, Vector2f(64, 64));
	init();

}


ControlPoly::~ControlPoly()
{

}
