#include <iostream>
#include <vector>
#include <map>
using namespace std;
#include "glm/glm.hpp"
using namespace glm;
#include "Vertex.h";
#include "Mesh.h"

#pragma once
class Chunk
{
	private:
		vector<unsigned short> blocks; // blocks id
		Mesh mesh;

	public:
		vec3 position;

		vector<Vertex> CreateBlock(unsigned short int blockChunkId);
		unsigned short GetBlock(short int blockChunkId);
		unsigned short GetBlock(vec3 position);

		void Update();
		void Draw();
};

