#include "stdafx.h"
#include "ProjectileBase.h"
#include "gameState.h"


ProjectileBase::ProjectileBase(Vector2f position, Vector2f dimensions, Vector2f velocity, float angle, float restitution, float mass, std::string textureName) : Entity(position, dimensions, restitution, mass, 0 , 0)
{
	texture = new sf::Texture();
	texture->loadFromFile(GetCurrentWorkingDir() + "\\resources\\" + textureName + ".png");
	ProjectileBase::angle = angle;
	/*getGame()->CurrentLevel->spawnEntities(this);
	getGame()->CurrentLevel->addDrawable(this);*/
	RigidBody::velocity = velocity;
	ProjectileBase::angle = angle;

}

ProjectileBase::~ProjectileBase()
{

}

void ProjectileBase::onUpdate(float deltaTime) {
	ticksActive++;
	if (ticksActive > 1 * 240) {
		this->setDead();
	}

	if (velocity.x > 64.0f - 5) {
		velocity.x = 64.0f - 5;
	}

	if (velocity.x < -64.0f + 5) {
		velocity.x = -64.0f + 5;
	}

	if (velocity.y >  64.0f - 5) {
		velocity.y = 64.0f - 5;
	}

	if (velocity.y < -64.0f + 5) {
		velocity.y = -64.0f + 5;
	}

	//origin += velocity;

}

void ProjectileBase::spawn() {

}

void ProjectileBase::setDead() {
	//getGame()->CurrentLevel->removeDrawable(this);
	//getGame()->CurrentLevel->removeEntity(this);
	delete texture; //NB : IF A TEXTUREPOOL IS MADE THIS LINE MUST BE DELETED
	this->ProjectileBase::~ProjectileBase();
	//delete this;
}

void ProjectileBase::onCollision(Entity* collided) {

}

void ProjectileBase::move() {

	FloatRect AABB = FloatRect(origin - dimensions / 2.0f, dimensions);

	//if (!getGame()->getRenderArea()->intersects(AABB)) { //projectiles by default despawn when the leave the screen
	//	setDead();
	//	return;
	//}
}

void ProjectileBase::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

	sf::VertexArray drawn(sf::Quads);
	drawn.resize(4);

	drawn[0].position = origin - dimensions / 2.0f;
	drawn[1].position = origin - Vector2f(dimensions.x, -dimensions.y) / 2.0f;
	drawn[2].position = origin + dimensions / 2.0f;
	drawn[3].position = origin + Vector2f(dimensions.x, -dimensions.y) / 2.0f;

	drawn[0].texCoords = Vector2f(0, 0);
	drawn[1].texCoords = Vector2f(0, dimensions.y);
	drawn[2].texCoords = Vector2f(dimensions.x, dimensions.y);
	drawn[3].texCoords = Vector2f(dimensions.x, 0);

	states.transform.rotate(angle, origin);
	states.texture = texture;
	target.draw(drawn, states);
	states.transform *= getTransform();
} 

