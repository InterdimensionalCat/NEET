#include "stdafx.h"
#include "BackgroundEngine.h"

//Background that implements parallax scrolling with an arbitrary number of background layers

BackgroundEngine::BackgroundEngine(uint16_t numBG)
{
	for (int i = 0; i < numBG; i++) {
		layers.push_back(*new BackgroundLayer(i));
	}
}


BackgroundEngine::~BackgroundEngine()
{

}

void BackgroundEngine::draw(sf::RenderWindow* window, double interpol) {
	for (auto layer : layers) {
		layer.draw(window, interpol);
	}
}

void BackgroundEngine::move(sf::Vector2f movement) {
	for (auto layer : layers) {
		layer.move(movement);
	}
}
