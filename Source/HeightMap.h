#include <vector>
using namespace std;
#include "glm/glm.hpp"
using namespace glm;
#include "PerlinNoise.hpp"
using namespace siv;

#pragma once
class HeightMap
{
	private:
		PerlinNoise noise;

		const double frequency = 8.0;
		const int32_t octaves = 8;

	public:
		void CreateHeightMap(uint32_t seed);
		double GetColumnHeight(vec3 columnPosition);

};

