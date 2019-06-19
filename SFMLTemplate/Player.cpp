#include "stdafx.h"
#include "Player.h"
#include <iostream>
#include "Game.h"
#include "GameState.h"

//the player, it is assumed that the player moves based on input, currently it is also assumed that there is 1 player, may change

Player::Player(sf::Vector2f position) : Entity(position, Vector2f(128.0f, 256.0f), 0.01f, 100.0f, 0.2f, 0.9f), Animatable(getAnimation("Player_Idle1"))
{
	//getGame()->registerDrawable(this);
	flip = false;
}


Player::~Player()
{

}


void Player::onUpdate(float deltaTime) {

	animate();
	currentAnimation->onUpdate(deltaTime);

	sf::Vector2f unitHorz(abs(unitGravity.y), -abs(unitGravity.x));

	if (airTime > 0) {
		if (Keyboard::isKeyPressed(Keyboard::A)) {
			velocity -= accl * unitHorz;
		}

		if (Keyboard::isKeyPressed(Keyboard::D)) {
				velocity += accl * unitHorz;
		}

		//if (getManager()->isKeyPressed(Keyboard::Space) && airTime > 0) {
		//	velocity -= jmp * unitGravity;
		//	airTime = 0;
		//}
	}
	else {
		if (Keyboard::isKeyPressed(Keyboard::A)) {
			velocity -= accl / 4.0f * unitHorz;
		}

		if (Keyboard::isKeyPressed(Keyboard::D)) {
			velocity += accl / 4.0f * unitHorz;
		}
	}

	if (--airTime > 0) {
		velocity += grv * unitGravity;
	}
	else {
		airTime = 0;
		Vector2f normalVel = normGrav(velocity, unitGravity);
		if (normalVel.y < -1.5) {
			velocity = normalDivide(velocity, 1.075f * Vector2f(abs(unitGravity.x), abs(unitGravity.y)));
		}
		else {
			velocity += grv * unitGravity;
		}

	}


	if (unitGravity.y != 0) {
		int signum = velocity.x > 0 ? 1 : velocity.x < 0 ? -1 : 0;



		Vector2f realFriction = Vector2f(friction.x * unitHorz.x, friction.y * unitHorz.y)* vecSign(velocity).x;

		if (unitGravity.y < 0) {
			realFriction *= -1.0f;
		}

		velocity -= realFriction;
		int sig2 = velocity.x > 0 ? 1 : velocity.x < 0 ? -1 : 0;

		if (signum != sig2) { //ensure that velocity does not change the player's direction
			velocity.x = 0;
		}
	}
	else {
		int signum = velocity.y > 0 ? 1 : velocity.y < 0 ? -1 : 0;

		Vector2f realFriction = Vector2f(friction.x * unitHorz.x, friction.y * unitHorz.y)* vecSign(velocity).y;

		if (unitGravity.x < 0) {
			realFriction *= -1.0f;
		}

		velocity -= realFriction;
		int sig2 = velocity.y > 0 ? 1 : velocity.y < 0 ? -1 : 0;

		if (signum != sig2) { //ensure that velocity does not change the player's direction
			velocity.y = 0;
		}
	}


	friction = Vector2f(0, 0);


	//if (getManager()->isKeyPressed(sf::Keyboard::E)) {
	//	RigidBody::rotate(true);
	//}

	//if (getManager()->isKeyPressed(sf::Keyboard::Q)) {
	//	RigidBody::rotate(false);
	//}

	//if (getManager()->isKeyPressed(sf::Keyboard::Up)) {
	//	RigidBody::rotate(sf::Vector2f(0, -1));
	//}

	//if (getManager()->isKeyPressed(sf::Keyboard::Down)) {
	//	RigidBody::rotate(sf::Vector2f(0, 1));
	//}

	//if (getManager()->isKeyPressed(sf::Keyboard::Left)) {
	//	RigidBody::rotate(sf::Vector2f(-1, 0));
	//}

	//if (getManager()->isKeyPressed(sf::Keyboard::Right)) {
	//	RigidBody::rotate(sf::Vector2f(1, 0));
	//}


	if (heldGun != NULL) heldGun->onUpdate(deltaTime, origin);

		if (unitGravity.x != 0) {
			if (velocity.y > maxHorzSpd) {
				velocity.y = maxHorzSpd;
			}
			else {
				if (velocity.y < -maxHorzSpd) {
					velocity.y = -maxHorzSpd;
				}
			}
	
			if (velocity.x > maxVertSpd) {
				velocity.x = maxVertSpd;
			}
			else {
				if (velocity.x < -maxVertSpd) {
					velocity.x = -maxVertSpd;
				}
			}
	
		} else {
	
			if (velocity.x > maxHorzSpd) {
				velocity.x = maxHorzSpd;
			}
			else {
				if (velocity.x < -maxHorzSpd) {
					velocity.x = -maxHorzSpd;
				}
			}
	
			if (velocity.y > maxVertSpd) {
				velocity.y = maxVertSpd;
			}
			else {
				if (velocity.y < -maxVertSpd) {
					velocity.y = -maxVertSpd;
				}
			}
		}

}


void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const {

	sf::VertexArray drawn(sf::Quads);
	drawn.resize(4);


	sf::Vector2f originDim = Vector2f(128, 256);

	//stretches image rect by 64

	//drawn[0].position = origin - originDim / 2.0f - Vector2f(64, 64);
	//drawn[1].position = origin - Vector2f(originDim.x, -originDim.y) / 2.0f - Vector2f(64, 0);
	//drawn[2].position = origin + originDim / 2.0f - Vector2f(-64, 0);
	//drawn[3].position = origin + Vector2f(originDim.x, -originDim.y) / 2.0f - Vector2f(-64, 64);


	drawn[0].position = origin - originDim / 2.0f;
	drawn[1].position = origin - Vector2f(originDim.x, -originDim.y) / 2.0f;
	drawn[2].position = origin + originDim / 2.0f;
	drawn[3].position = origin + Vector2f(originDim.x, -originDim.y) / 2.0f;

	sf::Vector2f zOrigin = dimensions / 2.0f;
	sf::Vector2f offest = sf::Vector2f(originDim.x * (float)currentAnimation->currentFrame, 0);

	if (unitGravity == sf::Vector2f(0, 1) || unitGravity == sf::Vector2f(-1, 0)) {
		if (!flip) {
			drawn[0].texCoords = offest;
			drawn[1].texCoords = Vector2f(offest.x, offest.y + originDim.y);
			drawn[2].texCoords = Vector2f(offest.x + originDim.x, offest.y + originDim.y);
			drawn[3].texCoords = Vector2f(offest.x + originDim.x, offest.y);
		}
		else {
			drawn[0].texCoords = Vector2f(offest.x + originDim.x, offest.y);
			drawn[1].texCoords = Vector2f(offest.x + originDim.x, offest.y + originDim.y);
			drawn[2].texCoords = Vector2f(offest.x, offest.y + originDim.y);
			drawn[3].texCoords = offest;
		}
	}
	else {
		if (flip) {
			drawn[0].texCoords = offest;
			drawn[1].texCoords = Vector2f(offest.x, offest.y + originDim.y);
			drawn[2].texCoords = Vector2f(offest.x + originDim.x, offest.y + originDim.y);
			drawn[3].texCoords = Vector2f(offest.x + originDim.x, offest.y);
		}
		else {
			drawn[0].texCoords = Vector2f(offest.x + originDim.x, offest.y);
			drawn[1].texCoords = Vector2f(offest.x + originDim.x, offest.y + originDim.y);
			drawn[2].texCoords = Vector2f(offest.x, offest.y + originDim.y);
			drawn[3].texCoords = offest;
		}
	}


	float angle;

	if (unitGravity == Vector2f(0, 1)) {
		angle = 0.0f;
	}
	else {
		if (unitGravity == Vector2f(0, -1)) {
			angle = 180.0f;
		}
		else {
			if (unitGravity == Vector2f(1, 0)) {
				angle = 270.0f;
			}
			else {
				angle = 90.0f;
			}
		}
	}

	Texture* t;
	t = currentAnimation->animation;
	states.transform.rotate(angle, origin);
	states.texture = t;
	target.draw(drawn, states);
}

void Player::animate() {

	float gsp = unitGravity.x != 0 ? velocity.y : velocity.x;
	if (gsp > 1) {
		flip = false;
	}

	if (gsp < -1) {
		flip = true;
	}

	
	if (airTime <= 0) {
		currentAnimation = getAnimation("Player_Aerial1", currentAnimation);
	}
	else {
		if (abs(gsp) < 1) {
			currentAnimation = getAnimation("Player_Idle1", currentAnimation);
		}
		else {
			if (gsp > 1) {
				currentAnimation = getAnimation("Player_Move_Right2", currentAnimation);
			}
			else {
				currentAnimation = getAnimation("Player_Move_Left2", currentAnimation);
			}
		}
	}
}