#pragma once
#include "GunBase.h"
#include "BasicBullet.h"
class ShotGun :
	public GunBase
{
public:
	ShotGun(Vector2f position);
	~ShotGun();
	virtual bool shoot() override;
};

