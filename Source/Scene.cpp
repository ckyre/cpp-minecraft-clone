#include "Scene.h"
#include "Renderer.h"

Camera Scene::camera;

void Scene::Start()
{
	UpdateVisibleChunks();
}

void Scene::Update()
{
	camera.computeMatrices();

	UpdateVisibleChunks();
	DrawVisibleChunks();
}


void Scene::DrawVisibleChunks()
{
	for (Chunk chunk : visibleChunks)
	{
		chunk.Draw();
	}
}

void Scene::UpdateVisibleChunks()
{
	int newCameraChunkPositionX = camera.position.x / (Chunk::CHUNK_SIZE * Chunk::BLOCK_SIZE);
	int newCameraChunkPositionZ = camera.position.z / (Chunk::CHUNK_SIZE * Chunk::BLOCK_SIZE);
	if (cameraChunkPositionX != newCameraChunkPositionX || cameraChunkPositionZ != newCameraChunkPositionZ)
	{
		cameraChunkPositionX = newCameraChunkPositionX;
		cameraChunkPositionZ = newCameraChunkPositionZ;

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

}

void Scene::LoadChunk(vec3 chunkPosition)
{
	for (Chunk chunk : visibleChunks)
	{
		if (chunk.GetPosition() == chunkPosition)
			return;
	}

	Chunk chunk(chunkPosition, this);
	chunk.Update();

	visibleChunks.push_back(chunk);
}
