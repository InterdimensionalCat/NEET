#include "stdafx.h"
#include "Entity.h"


//Entities are data structures that are instantiated and perfrom some action in the game, Entites are assumed to not move at all, and as such their texture and hitbox position do not update
//Mobile entities (MOBs) should be instantiated as type MOB


Entity::Entity(float posX, float posY, std::string textureName, float sizeX, float sizeY)
{
	if (!texture.loadFromFile(GetCurrentWorkingDir() + "\\resources\\" + textureName + ".png")) {
		std::cout << "COULD NOT LOAD IMAGE" << std::endl;
	}

	sprite.setTexture(texture);
	sprite.setPosition(sf::Vector2f(posX, posY));

	AABB = new sf::FloatRect(posX, posY, sizeX, sizeY);


	pos = new sf::Vector2f(posX, posY);
}


Entity::~Entity()
{

}

void Entity::spawn() { //called when the entity is placed in the world

}

void Entity::onUpdate(float deltaTime) { //called every frame

}

void Entity::draw(sf::RenderWindow* window, double interpol) { //renders the entity to the screen
	currentAnimation->draw(window, interpol);
	if (debug) {
		sf::RectangleShape rect(sf::Vector2f(AABB->width, AABB->height));
		rect.setPosition(sf::Vector2f(AABB->left, AABB->top));
		rect.setOutlineColor(sf::Color::Red);
		rect.setOutlineThickness(2);
		rect.setFillColor(sf::Color(0,0,0,0));
		window->draw(rect);

	}
}

void Entity::setDead() { //called when the entitiy is removed from the world (but not necessasarily destroyed)

}

bool Entity::onVerticalCollision(sf::FloatRect intersectRect, Tile* tileIn) {
	return 0; //this is so bad
}

bool Entity::onHorizontalCollision(sf::FloatRect intersectRect, Tile* tileIn) {
	return 0;
}
