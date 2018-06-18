#include "stdafx.h"
#include "Tile.h"
#include <iostream>
#include <Windows.h>
#include <string>

std::unordered_map<std::string, sf::Texture*> texturePool;
sf::Texture* setTexture(std::string textureName);
uint16_t TILE_SIZE = 128;

Tile::Tile(float posX, float posY, std::string textureName) {
	Tile::posX = posX;
	Tile::posY = posY;
	Tile::AABB = new sf::FloatRect(posX, posY, TILE_SIZE, TILE_SIZE);



	//if (!texture.loadFromFile("C:\\Users\\bennett\\Desktop\\SFML\\resources\\" + textureName + ".png")) {
	//	std::cout << "COULD NOT LOAD IMAGE" << std::endl;
	//}

	texture.loadFromFile(GetCurrentWorkingDir() + "\\resources\\" + textureName + ".png");

	sprite.setTexture(*setTexture(textureName));
	sprite.setPosition(sf::Vector2f(posX, posY));
}


Tile::~Tile() {

}

void Tile::draw(sf::RenderWindow* window, double interpol) {
	window->draw(sprite);
	if (debug) {
		sf::RectangleShape rect(sf::Vector2f(AABB->width, AABB->height));
		rect.setPosition(sf::Vector2f(AABB->left, AABB->top));
		rect.setOutlineColor(sf::Color::Blue);
		rect.setOutlineThickness(2);
		rect.setFillColor(sf::Color(0, 0, 0, 0));
		window->draw(rect);

	}
}

bool Tile::collisionWithEntityVertical(Entity* eIn) {

	sf::FloatRect intersectRect;
	if (AABB->intersects(*eIn->AABB, intersectRect)) {
		if (intersectRect.height <= intersectRect.width) {
			eIn->onVerticalCollision(intersectRect, this);
			return true;
		}
	}

	return false;
}

bool Tile::collisionWithEntityHorizontal(Entity* eIn) {

	sf::FloatRect intersectRect;
	if (AABB->intersects(*eIn->AABB, intersectRect)) {
		if (intersectRect.height > intersectRect.width) {
			eIn->onHorizontalCollision(intersectRect, this);
			return true;
		}
	}
	return false;
}

sf::Texture* setTexture(std::string textureName) {
	for (std::pair<std::string, sf::Texture*> s : texturePool) {
		if (s.first == textureName) {
			return s.second;
		}
	}

	sf::Texture* texture = new sf::Texture();

	if (!texture->loadFromFile(GetCurrentWorkingDir() + "\\resources\\" + textureName + ".png")) {
		std::cout << "COULD NOT LOAD IMAGE" << std::endl;
		return texture;
	}

	//std::pair<std::string, sf::Texture> newTexture(textureName, *texture);
	texturePool.insert(std::make_pair(textureName, texture));
	return texture;
}

