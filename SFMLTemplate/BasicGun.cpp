#include "stdafx.h"
#include "BasicGun.h"
#include "GameState.h"


BasicGun::BasicGun(Vector2f position) : GunBase(position, Vector2f(128,64), 450, 0.01f, 15, 120.0f , true ,"BasicGun")
{

}


BasicGun::~BasicGun()
{

}

bool BasicGun::shoot() {
	if (GunBase::shoot()) {

		const float pi = 3.1415926535f;

		float angle = (2*pi / 8.0f) * dir;
		float mag = dimensions.x / 2.0f;

		//The 2pi makes an inaccuracy of 1 completely random angle and covers the unit circle twice(maybe lol)
		//angle += inaccuracy* 2 * pi * getRandom()->nextFloat();

		//wheras pi/2 makes an inaccuracy of 1 fire anywhere in the the 2 quadrants the player is facing in
		//angle += inaccuracy * pi / 2 * getRandom()->nextFloat();


		float velMag = 64.0f;
		Vector2f vel(velMag * cos(angle), velMag * sin(angle));

		Vector2f launchOffset(-mag * cos(angle), -mag * sin(angle));

		//if (getGame()->CurrentLevel->getTile(toTiles(origin.x - launchOffset.x), toTiles(origin.y - launchOffset.y)) != NULL || getGame()->CurrentLevel->getTile(toTiles(origin.x - launchOffset.x + vel.x), toTiles(origin.y - launchOffset.y + vel.y)) != NULL) {
		//	return false;
		//}

		BasicBullet* shot = new BasicBullet(origin - launchOffset, angle, vel);
		shot->spawn();

		return true;
	}

	return false;

}