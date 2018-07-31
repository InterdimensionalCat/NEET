#pragma once
#include "EntityLivingBase.h"
#include "Animatable.h"

class Player : public EntityLivingBase, public Animatable
{
public:
	Player(float posX, float posY, float sizeX, float sizeY);
	void onUpdate(float deltaTime) override;
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	~Player();
};

