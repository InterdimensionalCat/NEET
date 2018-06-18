#include "stdafx.h"
#include "State.h"
#include <string>


State::State()
{

}


State::~State()
{

}

void State::onUpdate(float deltaTime) {

}

void State::init() {

}
void State::enter() {

}
void State::draw(sf::RenderWindow* window, double interpol) {

}
void State::exit() {

}
std::string State::getName() {
	return ""; //lol why is this allowed
}