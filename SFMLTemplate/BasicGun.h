#pragma once
#include "stdafx.h"
#include "GunBase.h"
#include "BasicBullet.h"
class BasicGun :
	public GunBase
{
public:
	BasicGun(Vector2f position);
	~BasicGun();
	//virtual void onUpdate(float deltaTime, Vector2f newOrigin) override;
	virtual bool shoot() override;
};

