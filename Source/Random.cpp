#include "Random.h"

void Random::Start()
{
	// Random seed
	srand(time(NULL));
}

int Random::Range(int min, int max)
{
	return (rand() % max+ min);
}
