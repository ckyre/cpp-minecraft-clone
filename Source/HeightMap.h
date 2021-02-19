#include <vector>
using namespace std;
#include "glm/glm.hpp"
using namespace glm;

#pragma once
class HeightMap
{
	private:
		vector<unsigned short> heightValues;

	public:
		void UpdateHeightMap(vec3 cameraPosition);
		unsigned short GetColumnHeight(vec3 columnPosition);

};

