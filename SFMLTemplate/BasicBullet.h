#pragma once
#include "ProjectileBase.h"

class BasicBullet :
	public ProjectileBase
{
public:
	BasicBullet(float posX, float posY, double angle);
	~BasicBullet();
	virtual void move() override;
	virtual void onUpdate(float deltaTime) override;
	virtual void spawn() override;
	virtual void onCollision(Entity* collided) override;
};

