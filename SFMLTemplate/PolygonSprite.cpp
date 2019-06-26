#include "stdafx.h"
#include "PolygonSprite.h"
#include "TransformComp.h"


PolygonSprite::PolygonSprite(Color outlineColor) : Component("SquareSprite")
{
	color = outlineColor;
}


PolygonSprite::~PolygonSprite()
{

}

void PolygonSprite::init() {
	transform = masterObj->getComponent<TransformComp>();
}

void PolygonSprite::onUpdate(float deltaTime, GameMouse* mouse, GameKeyboard* keyboard) {
	//update the sprite position

}

void PolygonSprite::draw(RenderWindow* target) {
	ConvexShape draw;
	draw.setPointCount(transform->shape.points.size());
	for (int i = 0; i < transform->shape.points.size(); i++) {
		draw.setPoint(i, transform->shape.points.at(i));
	}
	draw.setOutlineColor(color);
	draw.setOutlineThickness(5);
	target->draw(draw);

	Vertex line[2];
	line[0].position = Vector2f(0, 500);
	line[0].color = Color();
	line[1].position = Vector2f(1920, 500);
	line[1].color = Color();
	target->draw(line, 2, Lines);
}
