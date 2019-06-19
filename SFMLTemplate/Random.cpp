#include "stdafx.h"
#include "Random.h"


Random::Random()
{
	srand((unsigned int)time(NULL));
}


Random::~Random()
{

}

float Random::nextFloat() {
	float ret = rand() / (float)RAND_MAX;
	ret -= 0.5;
	ret *= 2;
	return ret;
}
