#pragma once

#include <SFML\Graphics.hpp>
#include "Game.h"
#include <unordered_map>
#include <string>

//Engine class for animating stuff

class Animation
{
public:
	Animation(std::string textureName, int sizeX, int sizeY, uint16_t speed, int id);
	~Animation();
	sf::Texture* animation;
	sf::Sprite* currentFrame;
	uint16_t speed;
	void draw(sf::RenderWindow* window, double interpol);
	void advanceFrame();
	void reset();
	uint16_t frameCounter;
	int sizeX;
	int sizeY;
	std::string name;
	int id;
};

void addAnimation(Animation* animation);
Animation* getAnimation(std::string name);
Animation* getAnimation(std::string name, Animation* currentAnimation);
const int getIdFromName(std::string name);

extern std::unordered_map<std::string, Animation*> animationPool;

