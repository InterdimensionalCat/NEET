#pragma once
#ifndef player_h
#define player_h

#include "Animatable.h"
#include "GunBase.h"

#endif // !player_h

class Player : public Entity, public Animatable
{
public:
	Player(Vector2f position);
	~Player();
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	void onUpdate(float deltaTime) override;
	void animate();

	GunBase* heldGun;
};

const float maxVertSpd = 64;
const float maxHorzSpd = 16;
const float grv = 0.5f;
//const float accl = 1.2f;
const float accl = 3.0f;
const float jmp = 25.0f;
//const Vector2f maxVel(16, 16);

