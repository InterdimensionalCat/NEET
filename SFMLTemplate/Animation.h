#pragma once

#include <SFML\Graphics.hpp>
#include "Game.h"
#include <unordered_map>
#include <string>

//Engine class for animating stuff

class Animation : public sf::Drawable, public sf::Transformable
{
public:
	Animation(std::string textureName, int sizeX, int sizeY, uint16_t speed, int id, int maxFrames);
	~Animation();
	sf::Texture* animation;
	//sf::Sprite* currentFrame;
	uint16_t speed;
	//void draw(sf::RenderWindow* window, double interpol);
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	void onUpdate(float deltaTime);
	void advanceFrame();
	void reset();
	uint16_t frameCounter;
	uint16_t currentFrame;
	uint16_t maxFrame;
	//int sizeX;
	//int sizeY;
	sf::Vector2i size;
	std::string name;
	int id;
};

//animations are all pulled from the same animation pool initialized on startup, these are methods that register and give access to those animations

void addAnimation(Animation* animation);
Animation* getAnimation(std::string name);
Animation* getAnimation(std::string name, Animation* currentAnimation);
const int getIdFromName(std::string name);

extern std::unordered_map<std::string, Animation*> animationPool;

