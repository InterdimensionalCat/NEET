#pragma once
#include "Entity.h"

//Base class for projectiles, a projectile is defined as a nonliving object that can collide with both entities and tiles

class ProjectileBase : public Entity, sf::Drawable, Transformable
{
public:
	ProjectileBase(Vector2f position, Vector2f dimensions, Vector2f velocity, float angle, float restitution, float mass, std::string textureName);
	~ProjectileBase();
	//virtual void move() override;
	virtual void onUpdate(float deltaTime) override;
	virtual void spawn() override; //The spawn() function from entity will actually see some usage here, I am planning to add random rotations/pitch changes to make bullets more realistic
	virtual void setDead() override;
	virtual void move();
	virtual void onCollision(Entity* collided);
	//virtual void onCollision(Entity* collided) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Texture* texture;
	int ticksActive;
	float angle; //in radians
};

