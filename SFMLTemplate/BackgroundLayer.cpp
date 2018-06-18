#include "stdafx.h"
#include "BackgroundLayer.h"
#include <iostream>
#include <string>

//wrapping background layer, it is assumed that backgrounds are always of the size WIDTH x HEIGHT

BackgroundLayer::BackgroundLayer(uint16_t id)
{
	texture = new sf::Texture();
	if (!texture->loadFromFile(GetCurrentWorkingDir() + "\\resources\\background_" + std::to_string(id) + ".png")) {
		std::cout << "COULD NOT LOAD IMAGE" << std::endl;
	}

	layer1 = new sf::Sprite();

	texture->setRepeated(true); //NB | APPARENTLY THIS WILL NOT WORK ON OLDER GRAPHCIS CARDS HOPE NOBODY PLAYS THIS GAME WITH A TOASTER

	layer1->setTexture(*texture);
	layer1->setPosition(sf::Vector2f(0, 0));

	speed = 0.25;
}


BackgroundLayer::~BackgroundLayer()
{

}


void BackgroundLayer::draw(sf::RenderWindow* window, double interpol) {
	window->draw(*layer1);
}

void BackgroundLayer::move(sf::Vector2f movement) {
	layer1->setTextureRect(sf::IntRect(layer1->getTextureRect().left + (int)(movement.x*speed), layer1->getTextureRect().top, layer1->getTextureRect().width, layer1->getTextureRect().height));
}
