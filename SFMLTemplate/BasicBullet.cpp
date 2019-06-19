#include "stdafx.h"
#include "stdafx.h"
#include "BasicBullet.h"
#include <cmath>


BasicBullet::BasicBullet(Vector2f position, float angle, Vector2f velocity) : ProjectileBase(position, Vector2f(20,20), velocity,  angle, 0.5 , 5 , "BasicBullet")
{

}


BasicBullet::~BasicBullet()
{

}

void BasicBullet::move() {
	ProjectileBase::move();
}

void BasicBullet::onUpdate(float deltaTime) {
	ProjectileBase::onUpdate(deltaTime);
}

void BasicBullet::spawn() {
	//TODO : ADD RANDOM NUMBER TO ANGLE
}

void BasicBullet::onCollision(Entity* collided) {
	std::cout << "HIT AN ENTITY" << std::endl;
	setDead();
}
