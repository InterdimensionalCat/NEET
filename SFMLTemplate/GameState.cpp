#include "stdafx.h"
#include "GameState.h"
#include <algorithm>
#include "BasicGun.h"
#include "ShotGun.h"

float zoom = 2;



GameState::GameState()
{

}


GameState::~GameState()
{

}

void GameState::init() {

	//Registers tiles for the game

	//registerTileID(0xFFFFFFFF, "GrassTile");

	//Initialize the first level and the parallax engine

	Level* level1 = new Level(3, 3, "testLevel1");
	//Level* level1 = new Level(3, 2, "Level2");
	CurrentLevel = level1;

	renderArea = new sf::FloatRect(0, 0, WIDTH, HEIGHT);

	pEngine = new BackgroundEngine(2);
	pEngine->layers.at(1).speed = 0.5;

}

void GameState::enter() {

	//Initialize camera and set the game window to that camera

	sf::View camera(sf::FloatRect(0, 0, WIDTH, HEIGHT));
	camera.zoom(zoom);
	getGameWind()->setView(camera);

	//initialize player and add player to the first level

	std::vector<Entity*> entities;
	Player* player = new Player(Vector2f(200, 200));
	CurrentLevel->player = player;
	entities.push_back((Entity*)player);
	//BasicGun* gun = new BasicGun(player->origin - player->dimensions / 2.0f);
	ShotGun* gun = new ShotGun(player->origin - player->dimensions / 2.0f);
	player->heldGun = gun;
	//entities.push_back((Entity*)gun);
	CurrentLevel->addDrawable((sf::Drawable*)gun);

	//popluate the level

	CurrentLevel->populate(entities);

}

void GameState::onUpdate(float deltaTime) {
	CurrentLevel->onUpdate(deltaTime);
}

void GameState::draw(sf::RenderWindow* window, double interpol) {

	//moves the camera so that the player is near the middle of the screen (slightly below) 
	//unless the player hits the border, then the camera will not scroll out of bounds
	//the zoom factor is taken into account when calculating the camera to allow for variable zooming

	sf::Vector2u windowSize = window->getSize();
	//float cposX = std::max(CurrentLevel->player->pos->x + CurrentLevel->player->AABB->width / 2, (float)WIDTH / 2 * zoom);
	//float cposY = std::max(CurrentLevel->player->pos->y + CurrentLevel->player->AABB->height / 2 - 150 * zoom, (float)HEIGHT / 2 * zoom);

	float cposX = std::max(CurrentLevel->player->origin.x, (float)WIDTH / 2 * zoom);
	float cposY = std::max(CurrentLevel->player->origin.y - 150 * zoom, (float)HEIGHT / 2 * zoom);

	cposX = std::min(cposX, CurrentLevel->sizeX - (float)WIDTH / 2 * zoom);
	cposY = std::min(cposY, CurrentLevel->sizeY - (float)HEIGHT / 2 * zoom);
	ceil(cposX);
	ceil(cposY);
	sf::View newView = window->getView();
	window->setView(window->getDefaultView());
	sf::Vector2f pMovement(ceil(cposX - newView.getCenter().x), ceil(cposY - newView.getCenter().y));

	//updates the parallax background to move as the viewport moves

	pEngine->move(pMovement);
	pEngine->draw(window, interpol);
	newView.setCenter(cposX, cposY);
	window->setView(newView);

	//draws the level: note that anything out side the calculated renderArea will not be drawn.

	sf::FloatRect windowBounds(sf::Vector2f(newView.getCenter().x - WIDTH*zoom / 2 - TILE_SIZE, newView.getCenter().y - HEIGHT * zoom / 2 - TILE_SIZE), newView.getSize() + sf::Vector2f(TILE_SIZE, TILE_SIZE));
	renderArea->left = windowBounds.left - TILE_SIZE * partitionSize;
	renderArea->top = windowBounds.top - TILE_SIZE * partitionSize;
	renderArea->width = windowBounds.width + TILE_SIZE * partitionSize;
	renderArea->height = windowBounds.height + TILE_SIZE * partitionSize;
	CurrentLevel->draw(window, interpol, renderArea);

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

void GameState::registerDrawable(sf::Drawable* target) {
	CurrentLevel->addDrawable(target);
}

sf::FloatRect* GameState::getRenderArea() {
	return renderArea;
}
