#include "stdafx.h"
#include "Animation.h"

std::unordered_map<std::string, Animation*> animationPool;

Animation::Animation(std::string textureName, int sizeX, int sizeY, uint16_t speed, int id)
{
	animation = new sf::Texture();
	currentFrame = new sf::Sprite();
	animation->loadFromFile(GetCurrentWorkingDir() + "\\resources\\" + textureName + ".png");
	currentFrame->setTexture(*animation);
	currentFrame->setTextureRect(sf::IntRect(0,0,sizeX,sizeY));
	Animation::speed = speed;
	frameCounter = 0;
	Animation::sizeX = sizeX;
	Animation::sizeY = sizeY;
	name = textureName;
	Animation::id = id;
	//addAnimation(this); //this is now done in InitAnimations.cpp
}


Animation::~Animation()
{

}

void Animation::draw(sf::RenderWindow* window, double interpol) {
	if (++frameCounter >= speed) {
		advanceFrame();
	}

	sf::Vector2f pos = currentFrame->getPosition();
	currentFrame->setPosition(ceil(pos.x), ceil(pos.y));
	window->draw(*currentFrame);
	currentFrame->setPosition(pos);
}

void Animation::advanceFrame() {
	frameCounter = 0;
	if (currentFrame->getTextureRect().left + sizeX > animation->getSize().x) {
		reset();
	} else {
		currentFrame->setTextureRect(sf::IntRect(currentFrame->getTextureRect().left + sizeX, 0, sizeX, sizeY));
	}
}

void Animation::reset() {
	currentFrame->setTextureRect(sf::IntRect(0, 0, sizeX, sizeY));
}

void addAnimation(Animation* animation) {
	animationPool.insert(std::make_pair(animation->name, animation));
}

Animation* getAnimation(std::string name) {
	animationPool.at(name)->reset();
	return animationPool.at(name);
}

Animation* getAnimation(std::string name, Animation* currentAnimation) {
	if (currentAnimation->name != name) {
		animationPool.at(name)->reset();
	}

	return animationPool.at(name);
}

const int getIdFromName(std::string name) {
	return getAnimation(name)->id;
}
