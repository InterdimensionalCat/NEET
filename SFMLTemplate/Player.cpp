#include "stdafx.h"
#include "Player.h"
#include <iostream>
#include "SFMLTemplate.h"
#include "GameState.h"

//the player, it is assumed that the player moves based on input, currently it is also assumed that there is 1 player, may change

float maxSpeedX = 50;

Player::Player(float posX, float posY, std::string textureName, float sizeX, float sizeY) : EntityLivingBase(posX, posY, textureName, sizeX, sizeY, 1)
{
	
}


Player::~Player()
{

}

void Player::onUpdate(float deltaTime) {



	AABB->left = pos->x;
	AABB->top = pos->y;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		motion->y -= 3;
	} else {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			motion->y += 3;
		} else {
			if (abs(motion->y) < 1) {
				motion->y = 0;
			}
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		motion->x -= 100 * deltaTime;
	} else {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			motion->x += 100 * deltaTime;
		}
		else {
			motion->x /= (float)1.1;
			if (abs(motion->x) < 1) {
				motion->x = 0;
			}
		}
	}

	if (motion->x > maxSpeedX) {
		motion->x = maxSpeedX;
	} else {
		if (motion->x < -maxSpeedX) {
			motion->x = -maxSpeedX;
		}
	}

	motion->y += 2;

	if (getManager()->isKeyPressed(sf::Keyboard::Space)) {
		jump(3000*deltaTime);
	}

	Mob::onUpdate(deltaTime);
}