#pragma once
#include "GunBase.h"
#include "BasicBullet.h"

class BasicGun :
	public GunBase
{
public:
	BasicGun();
	~BasicGun();
	virtual void onUpdate(float deltaTime) override;
	virtual void shoot() override;
};

