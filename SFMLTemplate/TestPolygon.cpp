#include "stdafx.h"
#include "TestPolygon.h"


TestPolygon::TestPolygon(Vector2f position, polygon body)
{
	addComponent((Component*)new TransformComp(position));
	addComponent((Component*)new PolygonSprite(Color::Red));
}


TestPolygon::~TestPolygon()
{

}
