#include "Scene.h"

Camera Scene::camera;

void Scene::Start()
{
	CreateNoiseMap();

	// Generate world
	for (int x = 0; x < WORLD_SIZE; x++)
	{
		for (int z = 0; z < WORLD_SIZE; z++)
		{
			vec3 chunkPosition = vec3(x * (Chunk::CHUNK_SIZE*Chunk::BLOCK_SIZE), 0, z * (Chunk::CHUNK_SIZE*Chunk::BLOCK_SIZE));
			LoadChunk(chunkPosition);
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

unsigned short Scene::GetChunk(vec3 chunkPosition)
{
	for (unsigned short i = 0; i < chunks.size(); i++)
	{
		if (chunks[i].GetPosition() == chunkPosition)
			return i;
	}
}

unsigned short Scene::GetHeight(unsigned short chunkIndex, vec3 blockPosition)
{
	// Get height with block position
	return 0;
}

void Scene::CreateNoiseMap()
{
	heightMap.clear();
	for (unsigned short i = 0; i < WORLD_SIZE * Chunk::CHUNK_SIZE; i++)
	{
		heightMap.push_back(Random::Range(0, 15));
	}
}

void Scene::LoadChunk(vec3 chunkPosition)
{
	Chunk chunk(chunkPosition, this, chunks.size());
	chunk.Update();

	chunks.push_back(chunk);
}

void Scene::UnloadChunk(unsigned short chunkId)
{
	if (chunkId >= 0 && chunkId < chunks.size())
	{
		chunks.erase(chunks.begin() + chunkId);
	}
}
