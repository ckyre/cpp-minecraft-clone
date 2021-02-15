#include "Vertex.h"

vec3 position;
vec2 uvs;
//vec3 normals;

vector<float> Vertex::ToArray()
{
	vector<float> result;
	result.push_back(position.x);
	result.push_back(position.y);
	result.push_back(position.z);
	result.push_back(uvs.x);
	result.push_back(uvs.y);
	//result.push_back(normals.x);
	//result.push_back(normals.y);
	//result.push_back(normals.z);
	return result;
}

