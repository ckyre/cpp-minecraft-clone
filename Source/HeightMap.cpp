#include "HeightMap.h"
#include "Chunk.h"
#include "Scene.h"

void HeightMap::UpdateHeightMap(vec3 cameraPosition)
{
	heightValues.clear();
	for (unsigned short i = 0; i < ((Chunk::CHUNK_SIZE * Scene::WORLD_SIZE) * (Chunk::CHUNK_SIZE * Scene::WORLD_SIZE)); i++)
	{
		heightValues.push_back(Random::Range(0, 15));
	}
}

unsigned short HeightMap::GetColumnHeight(vec3 columnPosition)
{
	if (columnPosition.x >= 0 && columnPosition.x < (Chunk::CHUNK_SIZE * Scene::WORLD_SIZE))
	{
		if (columnPosition.z >= 0 && columnPosition.z < (Chunk::CHUNK_SIZE * Scene::WORLD_SIZE))
		{
			unsigned short index = columnPosition.x * (Chunk::CHUNK_SIZE * Scene::WORLD_SIZE) + columnPosition.z;
			if (index >= 0 && index < heightValues.size())
				return heightValues[index];
		}
	}
	return 0;
}
