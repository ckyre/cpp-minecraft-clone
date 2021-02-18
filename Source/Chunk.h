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
class Scene;

class Chunk
{
	private:
		vec3 position;
		vector<unsigned short> blocks; // blocks id
		Mesh mesh;

		Scene* scene;
		unsigned short sceneChunkIndex;

		vector<Vertex> CreateBlockMesh(vec3 blockPosition);
		unsigned short GetBlockType(short int blockChunkId);
		unsigned short GetBlockType(vec3 blockPosition);
		unsigned short GetBlockIndex(vec3 blockPosition);

	public:
		static const unsigned short CHUNK_SIZE = 16;
		static const unsigned short BLOCK_SIZE = 2;

		Chunk(vec3 _position, Scene* _scene, unsigned short _sceneChunkIndex);
		void SetBlock(vec3 blockPosition, unsigned short blockId);
		void Update();
		void Draw();

		vec3 inline GetPosition() { return position; }
};
