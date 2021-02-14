#include "Vertex.h"

vec3 position;
vec2 uvs;

vector<float> Vertex::ToArray()
{
	vector<float> result;
	result.push_back(position.x);
	result.push_back(position.y);
	result.push_back(position.z);
	//result.push_back(uvs.x);
	//result.push_back(uvs.y);
	return result;
}

