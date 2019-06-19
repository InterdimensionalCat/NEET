#pragma once
#include "ProjectileBase.h"
#include "stdafx.h"
class BasicBullet :
	public ProjectileBase
{
public:
	BasicBullet(Vector2f position, float angle, Vector2f velocity);
	~BasicBullet();
	virtual void move() override;
	virtual void onUpdate(float deltaTime) override;
	virtual void spawn() override;
	virtual void onCollision(Entity* collided) override;
};

