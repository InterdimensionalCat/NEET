#pragma once
#include "EntityLivingBase.h"

class Player : public EntityLivingBase
{
public:
	Player(float posX, float posY, std::string textureName, float sizeX, float sizeY);
	void onUpdate(float deltaTime) override;
	~Player();
};

