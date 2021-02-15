#include <vector>
using namespace std;
#include "Chunk.h"
#include "Camera.h"
#include "glm/glm.hpp"
using namespace glm;

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

