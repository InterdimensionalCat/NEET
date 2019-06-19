#pragma once
#include "stdafx.h"
#include "Tile.h"

const int partitionSize = 3;

class SpacialPartition
{
public:
	SpacialPartition(std::vector<Tile*>* tiles);
	SpacialPartition();
	~SpacialPartition();
	Tile* tiles[partitionSize][partitionSize];
	std::vector<Entity*>* entities;
	void addEntity(Entity* e);
	void removeEntity(Entity* e);
	void removeEntity(int index);
};

