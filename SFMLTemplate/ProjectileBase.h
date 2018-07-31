#pragma once
#include "Mob.h"

//Base class for projectiles, a projectile is defined as a nonliving object that can collide with both entities and tiles

class ProjectileBase : public Mob, sf::Drawable
{
public:
	ProjectileBase(float posX, float posY, float sizeX, float sizeY, double angle, std::string textureName);
	~ProjectileBase();
	virtual void move() override;
	virtual void onUpdate(float deltaTime) override;
	virtual void spawn() override; //The spawn() function from entity will actually see some usage here, I am planning to add random rotations/pitch changes to make bullets more realistic
	virtual void setDead() override;
	virtual void onCollision(Entity* collided) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Texture* renderTexture;
	sf::Sprite* renderSprite;
	sf::Uint16 timeActive;
	double angle; //in radians
};

