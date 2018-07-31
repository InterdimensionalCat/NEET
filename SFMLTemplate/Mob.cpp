#include "stdafx.h"
#include "Mob.h"
#include "Game.h"
#include "GameState.h"

//a MOB (Mobile Entity) is an Entity with movement capabilities, it is assumed that a mob is not controllable by the player, nor is it an NPC
//Living MOB's should be instantiated as the type EntityLivingBase
//since MOB's are the first movable game object in the heirarchy, this is where rotational support is added

Mob::Mob(float posX, float posY, float sizeX, float sizeY/*, Animation* defaultAnimation*/) : Entity(posX, posY, sizeX, sizeY/*, defaultAnimation*/)
{
	motion = new sf::Vector2f(0, 0);
}


Mob::~Mob()
{

}

void Mob::onUpdate(float deltaTime) {
	move();
	Entity::onUpdate(deltaTime);
}

void Mob::move() { //moves the MOB

}


//void Mob::draw(sf::RenderWindow* window, double interpol) {
//	currentAnimation->currentFrame->setPosition(pos->x, pos->y); //ensures that the sprite is always where the player is
//	Entity::draw(window, interpol);
//}

//sf::FloatRect Mob::getDefaultAABB() {
//	return sf::FloatRect(pos->x, pos->y, sizeX, sizeY);
//}
