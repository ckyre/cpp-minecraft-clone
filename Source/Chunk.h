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
		vec3 position;
		vector<unsigned short> blocks; // blocks id
		Mesh mesh;

	public:
		vector<Vertex> CreateBlock(vec3 blockLocalPosition);
		unsigned short GetBlock(short int blockChunkId);
		unsigned short GetBlock(vec3 position);

		void Start();
		void Update();
		void Draw();
};

