#pragma once
#ifndef GunBase_H
#define GunBase_H
#include "Entity.h"
#endif

class Entity;

class GunBase : public sf::Drawable, public sf::Transformable, public Entity
{
public:
	GunBase(Vector2f position, Vector2f dimensions, float rpm, float inaccuracy, float clipSize, float reloadTime, bool automatic, std::string textureName);
	~GunBase();
	virtual void onUpdate(float deltaTime, Vector2f newOrigin);
	virtual void reload();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual bool shoot();
	virtual void setDead();
	unsigned int dir;
	unsigned int clipSize;
	int currentClip;
	float rpm;
	float cooldownTime;
	float inaccuracy;
	float reloadTime;
	float ticksReloading;
	bool automatic;
	Texture* texture;
	Vector2f orign;
};