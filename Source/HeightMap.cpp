#include "HeightMap.h"
#include "Chunk.h"
#include "Scene.h"
# include <cassert>
# include <iostream>
# include <fstream>
# include <sstream>

void HeightMap::CreateNoise()
{
	noise = SimplexNoise();
}

float HeightMap::GetColumnHeight(vec3 columnPosition)
{
	float value = noise.fractal(octaves, columnPosition.x * frequency, columnPosition.z * frequency);
	value += 1;
	value *= 0.5;

	cout << value << endl;
	return value * 15;
}
