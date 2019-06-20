#include "stdafx.h"
#include "PolygonSprite.h"
#include "TransformComp.h"


PolygonSprite::PolygonSprite(Color outlineColor) : Component("SquareSprite")
{
	PolygonSprite::body = body;
	PolygonSprite::position = position;
	color = outlineColor;
}


PolygonSprite::~PolygonSprite()
{

}

void PolygonSprite::onUpdate(float deltaTime, GameMouse* mouse, GameKeyboard* keyboard) {
	//update the sprite position
	TransformComp* transform = masterObj->getComponent("Transform");
	if (transform != NULL) {
		body =
	}

}

void PolygonSprite::draw(RenderWindow* target) {
	ConvexShape draw;
	draw.setPointCount(body.points.size());
	for (int i = 0; i < body.points.size(); i++) {
		draw.setPoint(i, body.points.at(i));
	}
	draw.move(position);
	draw.setOutlineColor(color);
	draw.setOutlineThickness(5);
	target->draw(draw);
}
