#pragma once
#include "Mob.h"

class EntityLivingBase : public Mob
{
public:
	EntityLivingBase(float posX, float posY, std::string textureName, float sizeX, float sizeY, int hitpoints);
	virtual void damage(uint16_t damage);
	virtual void heal(uint16_t health);
	virtual void kill();
	void virtual onUpdate(float deltaTime) override;
	virtual bool onVerticalCollision(sf::FloatRect intersectRect, Tile* tileIn) override;
	virtual bool onHorizontalCollision(sf::FloatRect intersectRect, Tile* tileIn) override;
	virtual bool jump(float velocity);
	int hitpoints;
	int maxHitPoints;
	~EntityLivingBase();
};
