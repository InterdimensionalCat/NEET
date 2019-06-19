#include "stdafx.h"
#include "ShotGun.h"
#include "GameState.h"


ShotGun::ShotGun(Vector2f position) : GunBase(position, Vector2f(128, 64), 90, 0.3f, 7, 240.0f, false, "BasicGun")
{

}


ShotGun::~ShotGun()
{

}


bool ShotGun::shoot() {

	bool outcome = false;

	if (GunBase::shoot()) {

		const float pi = 3.1415926535f;

		for (int i = 0; i < 5; i++) {
			float angle = (2 * pi / 8.0f) * dir;
			float mag = dimensions.x / 2.0f;
			//angle += inaccuracy * pi / 2 * getRandom()->nextFloat();


			float velMag = 64.0f;
			Vector2f vel(velMag * cos(angle), velMag * sin(angle));

			Vector2f launchOffset(-mag * cos(angle), -mag * sin(angle));

			//if (getGame()->CurrentLevel->getTile(toTiles(origin.x - launchOffset.x), toTiles(origin.y - launchOffset.y)) != NULL || getGame()->CurrentLevel->getTile(toTiles(origin.x - launchOffset.x + vel.x), toTiles(origin.y - launchOffset.y + vel.y)) != NULL) {
			//	continue;
			//}

			BasicBullet* shot = new BasicBullet(origin - launchOffset, angle, vel);
			shot->spawn();

			outcome = true;
		}
	}

	return outcome;
}
