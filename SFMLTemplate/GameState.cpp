#include "stdafx.h"
#include "GameState.h"
#include <algorithm>

float zoom = 1.5;


GameState::GameState()
{

}


GameState::~GameState()
{

}

void GameState::init() {
	//REGISTER TILES FOR GAME

	registerTileID(0xFFFFFFFF, "GrassTile");

	Level* level1 = new Level(TILE_SIZE * 100, TILE_SIZE * 25, "LEVEL_F3");
	CurrentLevel = level1;

	pEngine = new BackgroundEngine(2);
	pEngine->layers.at(1).speed = 0.5;

}

void GameState::enter() {
	sf::View camera(sf::FloatRect(0, 0, 1920, 1080));
	camera.zoom(zoom);
	getGameWind()->setView(camera);
	std::vector<Entity*> entities;
	Player* player = new Player(100, 100, "Player", 128, 256);
	CurrentLevel->player = player;
	entities.push_back((Entity*)player);
	CurrentLevel->populate(entities);

}

void GameState::onUpdate(float deltaTime) {
	CurrentLevel->onUpdate(deltaTime);
}

void GameState::draw(sf::RenderWindow* window, double interpol) {
	sf::Vector2u windowSize = window->getSize();
	float cposX = std::max(CurrentLevel->player->pos->x + CurrentLevel->player->AABB->width / 2, (float)WIDTH / 2 * zoom);
	float cposY = std::max(CurrentLevel->player->pos->y + CurrentLevel->player->AABB->height / 2 - 150 * zoom, (float)HEIGHT / 2 * zoom);
	cposX = std::min(cposX, CurrentLevel->sizeX - (float)WIDTH / 2 * zoom);
	cposY = std::min(cposY, CurrentLevel->sizeY - (float)HEIGHT / 2 * zoom);
	sf::View newView = window->getView();

	window->setView(window->getDefaultView());
	sf::Vector2f pMovement(cposX - newView.getCenter().x, cposY - newView.getCenter().y);

	pEngine->move(pMovement);
	pEngine->draw(window, interpol);

	newView.setCenter(cposX, cposY);
	//newView.setRotation(5);
	window->setView(newView);
	sf::FloatRect renderArea(sf::Vector2f(newView.getCenter().x - WIDTH*zoom / 2 - TILE_SIZE, newView.getCenter().y - HEIGHT * zoom / 2 - TILE_SIZE), newView.getSize() + sf::Vector2f(TILE_SIZE, TILE_SIZE));

	CurrentLevel->draw(window, interpol, &renderArea);

}

void GameState::exit() {

}

float GameState::getZoom() {
	return zoom;
}

void nextLevel() {

}

std::string GameState::getName() {
	return 0; //lol why is this allowed
}
