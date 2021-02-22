#include <vector>
#include <iostream>
using namespace std;
#include "glm/glm.hpp"
using namespace glm;
#include "SimplexNoise.h"

#pragma once
class HeightMap
{
	private:
		SimplexNoise noise;

		const double frequency = 0.01;
		const int octaves = 8;

	public:
		void CreateNoise();
		float GetColumnHeight(vec3 columnPosition);

};

