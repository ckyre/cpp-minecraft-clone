#include "Scene.h"

Camera Scene::camera;

void Scene::GenerateWorld()
{
	// Generate world
	for (int x = 0; x < WORLD_SIZE; x++)
	{
		for (int z = 0; z < WORLD_SIZE; z++)
		{
			Chunk chunk(vec3(x * 32, -32, z * 32));
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
