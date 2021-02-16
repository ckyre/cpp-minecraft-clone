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
		const int WORLD_SIZE = 4;

	public:
		static Camera camera;

		void GenerateWorld();
		void Update();

};

