#include "stdafx.h"
#include "BasicGun.h"


BasicGun::BasicGun() : GunBase(0, 0, 128, 64, 10, "BasicGun")
{

}


BasicGun::~BasicGun()
{

}

void BasicGun::onUpdate(float deltaTime) {
	GunBase::onUpdate(deltaTime);
	cooldown--;
	if (cooldown < 0) {
		cooldown = 0;
	}

	if (getManager()->isKeyPressed(sf::Keyboard::LShift)&&cooldown < 1) {
		cooldown = maxCoolDown;
		shoot();
	}
}

void BasicGun::shoot() {
	BasicBullet* shot = new BasicBullet(pos->x + AABB->width, pos->y, 0);
	shot->spawn();
}