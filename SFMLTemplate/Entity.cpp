#include "stdafx.h"
#include "Entity.h"


Entity::Entity(sf::Vector2f position, sf::Vector2f dimensions, float restitution, float mass, float staticFriction, float dynamicFriction) : RigidBody(position, dimensions, restitution, mass, staticFriction, dynamicFriction)
{
}


Entity::~Entity()
{

}

void Entity::spawn() { //called when the entity is placed in the world

}

void Entity::onUpdate(float deltaTime) { //called every frame

}

void Entity::setDead() { //called when the entitiy is removed from the world (but not necessasarily destroyed)

}
