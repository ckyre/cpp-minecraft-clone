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
		//vec3 normals;

		vector<float> ToArray();

		bool operator<(const Vertex that) const
		{
			return memcmp((void*)this, (void*)&that, sizeof(Vertex)) > 0;
		};
};

