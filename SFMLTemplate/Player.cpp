#include "stdafx.h"
#include "Player.h"
#include <iostream>
#include "Game.h"
#include "GameState.h"

//the player, it is assumed that the player moves based on input, currently it is also assumed that there is 1 player, may change

float maxSpeedX = 35;

Player::Player(float posX, float posY, float sizeX, float sizeY) : EntityLivingBase(posX, posY, sizeX, sizeY, 1), Animatable(getAnimation("Player_Idle"))
{
	getGame()->registerDrawable(this);
}


Player::~Player()
{

}

void Player::onUpdate(float deltaTime) {

	currentAnimation->currentFrame->setPosition(*pos);

	if (isAerial) {
		currentAnimation = getAnimation("Player_Aerial", currentAnimation);
	}

	switch (currentAnimation->id) {
		case 1: //Player_Idle

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				motion->x -= 150 * deltaTime;
				currentAnimation = getAnimation("Player_Move_Left");
			} else {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
					motion->x += 150 * deltaTime;
					currentAnimation = getAnimation("Player_Move_Right");
				} else {
					motion->x /= (float)2;
					if (abs(motion->x) < 1) {
						motion->x = 0;
					}
				}
			}

			if (getManager()->isKeyPressed(sf::Keyboard::Space)) {
				//jump(2500*deltaTime);
				jump(42);
			}

			break;
		case 2: //Player_Move_Right

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				motion->x += 50 * deltaTime;
			} else {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
					if (abs(motion->x) >= maxSpeedX) {
						currentAnimation = getAnimation("Player_TurnRun_Left");
					} else {
						motion->x /= 2;
						currentAnimation = getAnimation("Player_Idle");
					}
				} else {
					motion->x /= (float)2;
					if (abs(motion->x) < 1) {
						motion->x = 0;
						currentAnimation = getAnimation("Player_Idle");
					}
				}
			}

			if (getManager()->isKeyPressed(sf::Keyboard::Space)) {
				//jump(2500*deltaTime);
				jump(42);
			}

			break;
		case 3: //Player_Move_Left

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				motion->x -= 50 * deltaTime;
			} else {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
					if (abs(motion->x) >= maxSpeedX) {
						currentAnimation = getAnimation("Player_TurnRun_Right");
					} else {
						motion->x /= 2;
						currentAnimation = getAnimation("Player_Idle");
					}
				} else {
					motion->x /= (float)2;
					if (abs(motion->x) < 1) {
						motion->x = 0;
						currentAnimation = getAnimation("Player_Idle");
					}
				}
			}

			if (getManager()->isKeyPressed(sf::Keyboard::Space)) {
				//jump(2500*deltaTime);
				jump(42);
			}

			break;
		case 4: //Player_TurnRun_Right

			motion->x += 100 * deltaTime;

			if (motion->x >= 0) {
				currentAnimation = getAnimation("Player_Idle");
			}

			break;
		case 5: //Player_turnRun_Left

			motion->x -= 100 * deltaTime;

			if (motion->x <= 0) {
				currentAnimation = getAnimation("Player_Idle");
			}

			break;

		case 6: //Player_Aerial

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				motion->x += 100 * deltaTime;
			} else {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
					motion->x -= 100 * deltaTime;
				} else {
					motion->x *= 0.95;
				}
			}

			if (!isAerial) {
				if (motion->x > 0) {
					currentAnimation = getAnimation("Player_Move_Left");
				} else {
					if (motion->x < 0) {
						currentAnimation = getAnimation("Player_Move_Right");
					} else {
						currentAnimation = getAnimation("Player_Idle");
					}
				}
			}

			break;
	}

	if (motion->x > maxSpeedX) {
		motion->x = maxSpeedX;
	} else {
		if (motion->x < -maxSpeedX) {
			motion->x = -maxSpeedX;
		}
	}

	if (isAerial) {
		motion->y += 2;
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && motion->y < 0) {
		motion->y /= 5;
	}

	Mob::onUpdate(deltaTime);
	currentAnimation->onUpdate(deltaTime);
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	currentAnimation->currentFrame->setPosition(*pos);
	Animatable::draw(target, states);
}
