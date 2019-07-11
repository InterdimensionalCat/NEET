#include "stdafx.h"
#include "PolygonSprite.h"
#include "TransformComp.h"


PolygonSprite::PolygonSprite(Color outlineColor)
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

	//AABB hull = transform->getMinAABB();
	//RectangleShape draw2;
	//draw2.setSize(hull.max - hull.min);
	//draw2.setPosition(hull.min);
	//draw2.setOutlineColor(Color::Black);
	//draw2.setFillColor(Color(0, 0, 0, 0));
	//draw2.setOutlineThickness(10);

	//target->draw(draw2);


	ConvexShape draw;
	draw.setPointCount(transform->shape.points.size());
	for (int i = 0; i < transform->shape.points.size(); i++) {
		draw.setPoint(i, transform->orient * transform->shape.points.at(i) + transform->position);
	}
	draw.setOutlineColor(color);
	draw.setOutlineThickness(5);
	target->draw(draw);

	Vertex axis[2];
	axis[0].position = transform->position;
	axis[1].position = transform->shape.points.at(0);

	axis[0].color = Color::Black;
	axis[1].color = Color::Black;

	target->draw(axis, 2, Lines);
}
