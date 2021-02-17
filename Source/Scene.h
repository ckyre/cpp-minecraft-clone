#include <vector>
using namespace std;
#include "glm/glm.hpp"
using namespace glm;
#include "Camera.h"
#include "Chunk.h"

#pragma once

class Scene
{
	private:
		vector<Chunk> chunks;

	public:
		static const unsigned short WORLD_SIZE = 4;

		static Camera camera;

		void GenerateWorld();
		void Update();

		void CreateNoiseMap();
		void LoadChunk(vec3 chunkPosition);
		void UnloadChunk(unsigned short chunkId);
		void UpdateChunk(unsigned short chunkId);

		Chunk GetChunk(vec3 chunkPosition);
};

