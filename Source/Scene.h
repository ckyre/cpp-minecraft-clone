#include <vector>
#include <cmath>
using namespace std;
#include "glm/glm.hpp"
using namespace glm;
#include "Camera.h"
#include "Chunk.h"
#include "Random.h"

#pragma once
class Scene
{
	private:
		vector<unsigned short> heightMap;
		vector<Chunk> chunks;
		int cameraChunkPositionX, cameraChunkPositionZ;

	public:
		static const unsigned short WORLD_SIZE = 4;
		static Camera camera;

		void Start();
		void Update();

		void CreateNoiseMap();
		void LoadChunk(vec3 chunkPosition);
		void LoadAllChunks();
		void UnloadChunk(unsigned short chunkId);

		unsigned short GetHeight(vec3 blockPosition);
		unsigned short GetChunkIndex(vec3 chunkPosition);
};

