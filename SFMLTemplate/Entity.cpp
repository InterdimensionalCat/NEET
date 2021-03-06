#include "stdafx.h"
#include "Entity.h"


//Entities are data structures that are instantiated and perfrom some action in the game, Entites are assumed to not move at all, and as such their texture and hitbox position do not update
//Mobile entities (MOBs) should be instantiated as type MOB


Entity::Entity(float posX, float posY, float sizeX, float sizeY/*, Animation* defaultAnimation*/)
{
	//currentAnimation = defaultAnimation;
	//currentAnimation->currentFrame->setPosition(posX, posY);
	pos = new sf::Vector2f(posX, posY);
	AABB = new sf::FloatRect(pos->x, pos->y, sizeX, sizeY);
	Entity::sizeX = sizeX;
	Entity::sizeY = sizeY;
}


Entity::~Entity()
{

}

void Entity::spawn() { //called when the entity is placed in the world

}

void Entity::onUpdate(float deltaTime) { //called every frame

}

//void Entity::draw(sf::RenderWindow* window, double interpol) { //renders the entity to the screen
//	currentAnimation->draw(window, interpol);
//	if (debug) {
//		sf::RectangleShape rect(sf::Vector2f(AABB->width, AABB->height));
//		rect.setPosition(sf::Vector2f(AABB->left, AABB->top));
//		rect.setOutlineColor(sf::Color::Red);
//		rect.setOutlineThickness(2);
//		rect.setFillColor(sf::Color(0,0,0,0));
//		window->draw(rect);
//
//	}
//}

void Entity::setDead() { //called when the entitiy is removed from the world (but not necessasarily destroyed)

}

void Entity::onCollision(Entity* collided) {

}
