#include <iostream>
#include <vector>
#include <map>
using namespace std;
#include "glm/glm.hpp"
using namespace glm;
#include "Vertex.h";

#pragma once
class Chunk
{
	public:
		vector<unsigned short> data; // key : bloc id; value : count

		vector<Vertex> CreateBlock(vec3 position);
		unsigned short GetBlock(int index);
		unsigned short GetBlock(vec3 position);

		void Start();
		void Update();
};

