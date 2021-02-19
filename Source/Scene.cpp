#include "Scene.h"
#include "Renderer.h"

Camera Scene::camera;

void Scene::Start()
{
	CreateNoiseMap();
	LoadAllChunks();
}

void Scene::Update()
{
	camera.computeMatrices();

	// Update chunks on camera move
	int newCameraChunkPositionX = camera.position.x / (Chunk::CHUNK_SIZE * Chunk::BLOCK_SIZE);
	int newCameraChunkPositionZ = camera.position.z / (Chunk::CHUNK_SIZE * Chunk::BLOCK_SIZE);
	if (cameraChunkPositionX != newCameraChunkPositionX || cameraChunkPositionZ != newCameraChunkPositionZ)
	{
		cameraChunkPositionX = newCameraChunkPositionX;
		cameraChunkPositionZ = newCameraChunkPositionZ;
		LoadAllChunks();
	}

	for (Chunk chunk : chunks)
	{
		chunk.Draw();
	}
}

void Scene::CreateNoiseMap()
{
	heightMap.clear();
	for (unsigned short i = 0; i < ((Chunk::CHUNK_SIZE * WORLD_SIZE) * (Chunk::CHUNK_SIZE * WORLD_SIZE)); i++)
	{
		heightMap.push_back(Random::Range(0, 15));
	}
}

void Scene::LoadChunk(vec3 chunkPosition)
{
	for (Chunk chunk : chunks)
	{
		if (chunk.GetPosition() == chunkPosition)
			return;
	}

	Chunk chunk(chunkPosition, this);
	chunk.Update();

	chunks.push_back(chunk);
}

void Scene::LoadAllChunks()
{
	for (int x = -(WORLD_SIZE / 2); x < (WORLD_SIZE / 2); x++)
	{
		for (int z = -(WORLD_SIZE / 2); z < (WORLD_SIZE / 2); z++)
		{
			float posX = (cameraChunkPositionX * (Chunk::CHUNK_SIZE * Chunk::BLOCK_SIZE)) + (x * (Chunk::CHUNK_SIZE * Chunk::BLOCK_SIZE));
			float posZ = (cameraChunkPositionZ * (Chunk::CHUNK_SIZE * Chunk::BLOCK_SIZE)) + (z * (Chunk::CHUNK_SIZE * Chunk::BLOCK_SIZE));
			vec3 chunkPosition = vec3(posX, 0, posZ);
			LoadChunk(chunkPosition);
		}
	}
}

void Scene::UnloadChunk(unsigned short chunkId)
{
	if (chunkId >= 0 && chunkId < chunks.size())
	{
		chunks.erase(chunks.begin() + chunkId);
	}
}


unsigned short Scene::GetChunkIndex(vec3 chunkPosition)
{
	for (unsigned short i = 0; i < chunks.size(); i++)
	{
		if (chunks[i].GetPosition() == chunkPosition)
			return i;
	}
}

unsigned short Scene::GetHeight(vec3 blockPosition)
{
	if (blockPosition.x >= 0 && blockPosition.x < (Chunk::CHUNK_SIZE * WORLD_SIZE))
	{
		if (blockPosition.z >= 0 && blockPosition.z < (Chunk::CHUNK_SIZE * WORLD_SIZE))
		{
			unsigned short index = blockPosition.x * (Chunk::CHUNK_SIZE * WORLD_SIZE) + blockPosition.z;

			if (index >= 0 && index < heightMap.size())
			{
				return heightMap[index];
			}
		}
	}
	return 0;
}
