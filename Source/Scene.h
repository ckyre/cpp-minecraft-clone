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

	public:
		static Camera camera;

		void GenerateWorld();
		void Update();

};

