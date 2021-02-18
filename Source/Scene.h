#include <vector>
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

	public:
		static const unsigned short WORLD_SIZE = 4;
		static Camera camera;

		void Start();
		void Update();

		void CreateNoiseMap();
		void LoadChunk(vec3 chunkPosition);
		void UnloadChunk(unsigned short chunkId);

		unsigned short GetHeight(unsigned short chunkIndex, vec3 blockPosition);
		unsigned short GetChunk(vec3 chunkPosition);
};

