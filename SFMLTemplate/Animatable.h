#pragma once
#include "animation.h"

//Allows an object to render an animation as opposed to a static sprite

class animation;

class Animatable : public sf::Drawable, public sf::Transformable
{
public:
	Animatable();
	Animatable(Animation* defaultAnimation);
	~Animatable();
	Animation* currentAnimation;
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

