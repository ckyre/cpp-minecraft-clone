#include <vector>
#include <cmath>
using namespace std;
#include "glm/glm.hpp"
using namespace glm;
#include "Camera.h"
#include "Chunk.h"
#include "Random.h"
#include "HeightMap.h"

#pragma once
class Scene
{
	private:
		vector<Chunk> visibleChunks;
		int cameraChunkPositionX, cameraChunkPositionZ;

	public:
		static const unsigned short WORLD_SIZE = 4;
		static Camera camera;

		HeightMap heightMap;

		void Start();
		void Update();

		void LoadChunk(vec3 chunkPosition);
		void UpdateVisibleChunks();
		void DrawVisibleChunks();

};

