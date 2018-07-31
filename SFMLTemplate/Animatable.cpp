#include "stdafx.h"
#include "Animatable.h"


Animatable::Animatable()
{

}


Animatable::Animatable(Animation* defaultAnimation)
{
	currentAnimation = defaultAnimation;
}

Animatable::~Animatable()
{

}

void Animatable::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(*currentAnimation, states);
}