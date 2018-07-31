#include "stdafx.h"
#include "GunBase.h"
#include "GameState.h"


GunBase::GunBase(float posX, float posY, float sizeX, float sizeY, int cooldown, std::string textureName) : Entity(posX, posY, sizeX, sizeY)
{
	texture = new sf::Texture();
	sprite = new sf::Sprite();
	texture->loadFromFile(GetCurrentWorkingDir() + "\\resources\\" + textureName + ".png");
	sprite->setTexture(*texture);
	sprite->setPosition(*pos);
	maxCoolDown = cooldown;
}


GunBase::~GunBase()
{

}


void GunBase::onUpdate(float deltaTime) {
	pos->x = getGame()->CurrentLevel->player->pos->x + 32;
	pos->y = getGame()->CurrentLevel->player->pos->y + 64;
	AABB->left = pos->x;
	AABB->top = pos->y;
	sprite->setPosition(*pos);
}

void GunBase::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(*sprite, states);
	if (debug) {
		sf::RectangleShape rect(sf::Vector2f(AABB->width, AABB->height));
		rect.setPosition(sf::Vector2f(AABB->left, AABB->top));
		rect.setOutlineColor(sf::Color::Red);
		rect.setOutlineThickness(2);
		rect.setFillColor(sf::Color(0,0,0,0));
		target.draw(rect);
	}
}

void GunBase::shoot() {

}

void GunBase::setDead() {

}
