#include "stdafx.h"
#include "SpacialPartition.h"


SpacialPartition::SpacialPartition(std::vector<Tile*>* tiles)
{
	for (int i = 0; i < tiles->size(); i++) {
		int j = 0;
		while (i >= partitionSize) {
			j++;
			i -= partitionSize;
		}
		SpacialPartition::tiles[j][i] = tiles->at(i);
	}

	entities = new std::vector<Entity*>();

}


SpacialPartition::SpacialPartition()
{
	entities = new std::vector<Entity*>();
}



SpacialPartition::~SpacialPartition()
{

}

void SpacialPartition::addEntity(Entity* e) {
	if (std::find(entities->begin(), entities->end(), e) == entities->end()) {
		entities->push_back(e);
	}
}

void SpacialPartition::removeEntity(Entity* e) {
	entities->erase(std::find(entities->begin(), entities->end(), e));
	//for (int i = 0; i < entities->size(); i++) {
	//	if (entities->at(i) == e) {
	//		entities->erase(entities->begin() + i);
	//		return;
	//	}
	//}
}

void SpacialPartition::removeEntity(int index) {
	entities->erase(entities->begin() + index);
}
