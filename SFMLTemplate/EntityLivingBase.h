#pragma once
#include "Mob.h"

//TODO: WILL INHERIT TRANSFORMABLE AND SUPPORT GRAVITY ROTATIONS

class EntityLivingBase : public Mob
{
public:
	EntityLivingBase(float posX, float posY, float sizeX, float sizeY, int hitpoints/*, Animation* defaultAnimation*/);
	virtual void damage(uint16_t damage);
	virtual void heal(uint16_t health);
	virtual void kill();
	void virtual onUpdate(float deltaTime) override;
	virtual void move() override;
	virtual bool jump(float velocity);
	sf::Vector2f calculatePoints(int id);
	int hitpoints;
	int maxHitPoints;
	bool isAerial;
	~EntityLivingBase();
};

