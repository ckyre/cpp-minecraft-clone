#include <iostream>
#include <vector>
#include <map>
using namespace std;
#include "glm/glm.hpp"
using namespace glm;
#include "Vertex.h"
#include "Mesh.h"
#include "Renderer.h"

#pragma once
class Chunk
{
	private:
		vec3 position;
		vector<unsigned short> blocks; // blocks id
		Mesh mesh;
		Scene parentScene;

		vector<Vertex> CreateBlockMesh(unsigned short int blockChunkId);
		unsigned short GetBlock(short int blockChunkId);
		unsigned short GetBlock(vec3 position);

	public:

		Chunk(Scene _parentScene, vec3 _position);
		void Update();
		void Draw();
};

