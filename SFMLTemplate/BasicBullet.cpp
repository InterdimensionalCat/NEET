#include "stdafx.h"
#include "BasicBullet.h"
#include <cmath>


BasicBullet::BasicBullet(float posX, float posY, double angle) : ProjectileBase(posX, posY, 20, 20, angle, "BasicBullet")
{

}


BasicBullet::~BasicBullet()
{

}

void BasicBullet::move() {
	ProjectileBase::move();
}

void BasicBullet::onUpdate(float deltaTime) {
	motion->x = 10 * cos(angle);
	motion->y = 10 * sin(angle);
	ProjectileBase::onUpdate(deltaTime);
}

void BasicBullet::spawn() {
	//TODO : ADD RANDOM NUMBER TO ANGLE
}

void BasicBullet::onCollision(Entity* collided) {
	std::cout << "HIT AN ENTITY" << std::endl;
	setDead();
}
