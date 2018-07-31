#include "stdafx.h"
#include "ProjectileBase.h"
#include "gameState.h"


ProjectileBase::ProjectileBase(float posX, float posY, float sizeX, float sizeY, double angle, std::string textureName) : Mob(posX, posY, sizeX, sizeY)
{
	renderTexture = new sf::Texture();
	renderSprite = new sf::Sprite();
	renderTexture->loadFromFile(GetCurrentWorkingDir() + "\\resources\\" + textureName + ".png");
	renderSprite->setTexture(*renderTexture);
	renderSprite->setPosition(*pos);
	ProjectileBase::angle = angle;
	getGame()->CurrentLevel->spawnEntities(this);
	getGame()->CurrentLevel->addDrawable(this);

}

ProjectileBase::~ProjectileBase()
{

}

void ProjectileBase::onUpdate(float deltaTime) {
	timeActive++;
	for (auto t : *getGame()->CurrentLevel->tileMap->tiles) {
		if (t == NULL) continue;
		if (t->AABB->intersects(*AABB)) {
			setDead();
			return;
		}
	}
	Mob::onUpdate(deltaTime);
}

void ProjectileBase::spawn() {

}

void ProjectileBase::setDead() {
	getGame()->CurrentLevel->removeDrawable(this);
	getGame()->CurrentLevel->removeEntity(this);
	delete renderTexture; //NB : IF A TEXTUREPOOL IS MADE THIS LINE MUST BE DELETED
	delete renderSprite;
	delete pos;
	delete motion;
	delete AABB;
	//this->ProjectileBase::~ProjectileBase();
	delete this;
}

void ProjectileBase::onCollision(Entity* collided) {

}

void ProjectileBase::move() {

	if (!getGame()->getRenderArea()->intersects(*AABB)) { //projectiles by default despawn when the leave the screen
		setDead();
		return;
	}

	pos->x += motion->x;
	pos->y += motion->y;
	AABB->left = pos->x;
	AABB->top = pos->y;
	renderSprite->setPosition(*pos);
}

void ProjectileBase::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*renderSprite, states);
}

