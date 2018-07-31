#pragma once
#include "Mob.h"
class GunBase : public Entity, public sf::Drawable, public sf::Transformable
{
public:
	GunBase(float posX, float posY, float sizeX, float sizeY, int cooldown, std::string textureName);
	~GunBase();
	virtual void onUpdate(float deltaTime) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void shoot();
	virtual void setDead();
	sf::Texture* texture;
	sf::Sprite* sprite;
	int cooldown;
	int maxCoolDown;
};