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
	transform = masterObj->getComponent<TransformComp>("Transform");
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
	draw.move(transform->position);
	draw.setOutlineColor(color);
	draw.setOutlineThickness(5);
	target->draw(draw);
}
