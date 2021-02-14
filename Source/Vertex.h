#include <vector>
using namespace std;
#include <glm/glm.hpp>
using namespace glm;

#pragma once
class Vertex
{
	public:
		vec3 position;
		vec2 uvs;

		vector<float> ToArray();
};

