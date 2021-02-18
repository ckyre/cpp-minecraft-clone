#include "Scene.h"

Camera Scene::camera;

void Scene::Start()
{
	CreateNoiseMap();
}

void Scene::Update()
{
	camera.computeMatrices();

	// On camera move, load/unload chunks
	vec3 _cameraClosestChunk = vec3(GetClosestChunkCoordinate(camera.position.x), 0, GetClosestChunkCoordinate(camera.position.z));
	if (cameraClosestChunk != _cameraClosestChunk)
	{
		cameraClosestChunk = _cameraClosestChunk;
		//chunks.clear();
		camera.sensivity = 0;
		int chunkSize = (WORLD_SIZE * Chunk::CHUNK_SIZE * Chunk::BLOCK_SIZE);
		for (int x = 0; x < WORLD_SIZE; x++)
		{
			for (int z = 0; z < WORLD_SIZE; z++)
			{
				float posX = (cameraClosestChunk.x - (chunkSize / 2) + (x * (Chunk::CHUNK_SIZE * Chunk::BLOCK_SIZE)));
				float posZ = (cameraClosestChunk.z - (chunkSize / 2) + (z * (Chunk::CHUNK_SIZE * Chunk::BLOCK_SIZE)));
				vec3 chunkPosition = vec3(posX, 0, posZ);
				LoadChunk(chunkPosition);
			}
		}
		camera.sensivity = 0.1f;
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

int Scene::GetClosestChunkCoordinate(float coordinate)
{
	int remainder = abs((int)coordinate) % Chunk::CHUNK_SIZE;
	if (remainder == 0)
		return Chunk::CHUNK_SIZE;

	if (coordinate < 0)
		return -(abs(coordinate) - remainder);
	else
		return coordinate + Chunk::CHUNK_SIZE - remainder;
}