#pragma once
class Component
{
public:
	Component(string tag);
	~Component();

	void onUpdate(float deltaTime, GameMouse* mouse, GameKeyboard* keyboard);
	void draw(RenderWindow* target);
	string tag;
};

