#include <iostream>
#include <vector>
#include <map>
using namespace std;
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
using namespace glm;
#include "Vertex.h"
#include "Mesh.h"

#pragma once
class Chunk
{
	private:
		vec3 position;
		vector<unsigned short> blocks; // blocks id
		Mesh mesh;

		vector<Vertex> CreateBlockMesh(vec3 blockPosition);
		unsigned short GetBlockId(short int blockChunkId);
		unsigned short GetBlockId(vec3 blockPosition);

	public:
		static const unsigned short CHUNK_SIZE = 16;
		static const unsigned short BLOCK_SIZE = 2;

		Chunk(vec3 _position);
		void Update();
		void Draw();
};
