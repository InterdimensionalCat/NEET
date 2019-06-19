#pragma once
#ifndef testenemy_h
#define testenemy_h
#include "stdafx.h"
#include "Entity.h"
#include "Animatable.h"
#include "GameState.h"
#endif

class TestEnemy :
	public Entity,
	public Animatable
{
public:
	TestEnemy(Vector2f position);
	~TestEnemy();
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	virtual void onUpdate(float deltaTime) override;
	virtual void setDead() override;

	int cycle = 60 * 2;
	int ticksMoving;
	float constVel = 1.2f;
};

