#include "stdafx.h"
#include "TestSquare.h"


TestSquare::TestSquare(Vector2f position, Vector2f dimensions)
{
	addComponent((Component*)new TransformComp(position));
	addComponent((Component*)new TestSquareSprite(dimensions, position, Color::Red));
}


TestSquare::~TestSquare()
{

}
