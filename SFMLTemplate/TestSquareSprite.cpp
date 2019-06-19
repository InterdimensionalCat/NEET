#include "stdafx.h"
#include "TestSquareSprite.h"


TestSquareSprite::TestSquareSprite(Vector2f dimensions, Vector2f position, Color outlineColor) : Component("SquareSprite")
{
	TestSquareSprite::dimensions = dimensions;
	TestSquareSprite::position = position;
	color = outlineColor;
}


TestSquareSprite::~TestSquareSprite()
{

}

void TestSquareSprite::onUpdate(float deltaTime, GameMouse* mouse, GameKeyboard* keyboard) {
	//update the sprite position
}

void TestSquareSprite::draw(RenderWindow* target) {
	RectangleShape draw(dimensions);
	draw.move(position);
	draw.setOutlineColor(color);
	draw.setOutlineThickness(5);
	target->draw(draw);
}
