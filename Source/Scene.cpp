#include "Scene.h"

Camera Scene::camera;

void Scene::GenerateWorld()
{
	// Generate world
	for (int x = 0; x < WORLD_SIZE; x++)
	{
		for (int z = 0; z < WORLD_SIZE; z++)
		{
			vec3 chunkPosition = vec3(x * (Chunk::CHUNK_SIZE*Chunk::BLOCK_SIZE), 0, z * (Chunk::CHUNK_SIZE*Chunk::BLOCK_SIZE));
			Chunk chunk(chunkPosition);
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
