#pragma once
#include "GameObject.h"
class Terrain :
	public GameObject
{
public:
	Terrain(vector<Vector2f> points, Vector2f position, Vector2f dimensions, Scene* master);
	Terrain(Vector2f position, Vector2f dimensions, Scene* master);
	~Terrain();
};
