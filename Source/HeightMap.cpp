#include "HeightMap.h"
#include "Chunk.h"
#include "Scene.h"
# include <cassert>
# include <iostream>
# include <fstream>
# include <sstream>

void HeightMap::CreateHeightMap(uint32_t seed)
{
	PerlinNoise _noise(seed);
	noise = _noise;
}

double HeightMap::GetColumnHeight(vec3 columnPosition)
{
	double value = noise.accumulatedOctaveNoise2D_0_1(columnPosition.x, columnPosition.z, octaves) * 16;
	cout << value << endl;
	return value;
}
