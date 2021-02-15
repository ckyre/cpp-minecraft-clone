#include "Scene.h"

Camera Scene::camera;

void Scene::GenerateWorld()
{
	// Generate world
	for (int x = 0; x < 1; x += 16)
	{
		for (int z = 0; z < 1; z += 16)
		{
			Chunk chunk;
			chunk.position = vec3(x - 8, 0, z - 8);
			chunk.Update();
			chunks.push_back(chunk);
		}
	}
}

void Scene::Update()
{
	camera.computeMatrices();

	for (Chunk chunk : chunks)
	{
		chunk.Draw();
	}
}
