#pragma once
#include<SFML\Graphics.hpp>
#include <string>

class MenuButton
{
public:
	MenuButton(std::string unselected, std::string selected, std::string name, float posX, float posY);
	~MenuButton();
	bool selected;
	void draw(sf::RenderWindow* window, double interpol);
	void init();
	float posX;
	float posY;
	sf::IntRect AABB;
private:
	std::string Sselected;
	std::string Sunselected;
	sf::Sprite unselectedSprite;
	sf::Sprite selectedSprite;
	sf::Texture unselectedTexture;
	sf::Texture selectedTexture;
};

