#pragma once
#include <SFML\graphics.hpp>
#include "Game.h"
#include <string>
#include <iostream>
#include "RigidBody.h"


//Base class for an Entity (or actor), note that entity does not natively support being drawn to the screen

class Entity : public RigidBody
{
public:
	Entity(Vector2f position, Vector2f dimensions, float restitution, float mass, float staticFriction, float dynamicFriction);
	~Entity();
	virtual void onUpdate(float deltaTime);
	virtual void spawn();
	virtual void setDead();
};

