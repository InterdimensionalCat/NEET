#include "stdafx.h"
#include "TestPolygon.h"


TestPolygon::TestPolygon(Vector2f position, polygon body)
{
	TransformComp* transform = new TransformComp(position);
	addComponent(new PolygonSprite(Color::Red));
	addComponent(transform);
	init();

}


TestPolygon::~TestPolygon()
{

}
