#pragma once
#include "stdafx.h"
#include "GunBase.h"

GunBase::GunBase(Vector2f position, Vector2f dimensions, float rpm, float inaccuracy, float clipSize, float reloadTime, bool automatic, std::string textureName) : Entity(position, dimensions, 0, 0, 0, 0)
{
	texture = new sf::Texture();
	texture->loadFromFile(GetCurrentWorkingDir() + "\\resources\\" + textureName + ".png");
	GunBase::rpm = rpm;
	GunBase::inaccuracy = inaccuracy;
	GunBase::clipSize = clipSize;
	GunBase::currentClip = clipSize;
	GunBase::reloadTime = reloadTime;
	GunBase::ticksReloading = 0;
	GunBase::automatic = automatic;
}


GunBase::~GunBase()
{

}


void GunBase::onUpdate(float deltaTime, Vector2f newOrigin) {
	origin = newOrigin;

	//std::cout << newOrigin.x << " " << newOrigin.y << std::endl;

	cooldownTime -= deltaTime;

	if (cooldownTime <= 0) {
		cooldownTime = 0;
	}


	for (int i = 0; i < 1; i++) {
		if (Keyboard::isKeyPressed(Keyboard::D)) {

			flip = false;

			if (Keyboard::isKeyPressed(Keyboard::W)) {
				dir = 7;
				break;
			}
			else {
				dir = 0;
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::W)) {
			if (Keyboard::isKeyPressed(Keyboard::A)) {
				flip = true;
				dir = 5;
				break;
			}
			else {
				dir = 6;
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::A)) {

			flip = true;

			if (Keyboard::isKeyPressed(Keyboard::S)) {
				dir = 3;
				break;
			}
			else {
				dir = 4;
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::S)) {
			if (Keyboard::isKeyPressed(Keyboard::D)) {

				flip = false;

				dir = 1;
				break;
			}
			else {
				dir = 2;
			}
		}
	}

	if (--ticksReloading <= 0) {
		if (automatic) {
			if (Mouse::isButtonPressed(sf::Mouse::Left)) {
				shoot();
			}
		}
		else {
			/*if (getManager()->isButtonPressed(sf::Mouse::Left)) {
				shoot();
			}*/
		}
	}
}


void GunBase::reload() {
	currentClip = clipSize;
	ticksReloading = reloadTime;
}


bool GunBase::shoot() {
	if (cooldownTime > 0) {
		return false;
	}
	else {
		cooldownTime = (60.0f / rpm);
		if (--currentClip <= 0) {
			reload();
		}
		return true;
	}
}

void GunBase::setDead() {

}


void GunBase::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::VertexArray drawn(sf::Quads);
	drawn.resize(4);


	sf::Vector2f originDim = Vector2f(128, 64);


	drawn[0].position = origin - originDim / 2.0f;
	drawn[1].position = origin - Vector2f(originDim.x, -originDim.y) / 2.0f;
	drawn[2].position = origin + originDim / 2.0f;
	drawn[3].position = origin + Vector2f(originDim.x, -originDim.y) / 2.0f;

	sf::Vector2f zOrigin = dimensions / 2.0f;


	if (!flip) {
		drawn[0].texCoords = Vector2f(0, 0);
		drawn[1].texCoords = Vector2f(0, originDim.y);
		drawn[2].texCoords = Vector2f(originDim.x, originDim.y);
		drawn[3].texCoords = Vector2f(originDim.x, 0);
	}
	else {
		drawn[0].texCoords = Vector2f(0, originDim.y);
		drawn[1].texCoords = Vector2f(0, 0);
		drawn[2].texCoords = Vector2f(originDim.x, 0);
		drawn[3].texCoords = Vector2f(originDim.x, originDim.y);
	}

	float angle;

	angle = (360.0f / 8.0f) * dir;

	states.transform.rotate(angle, origin);
	states.texture = texture;
	target.draw(drawn, states);
	states.transform *= getTransform();
}
