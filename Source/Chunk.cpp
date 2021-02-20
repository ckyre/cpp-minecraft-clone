#include "Scene.h"
#include "Chunk.h"
#include "Renderer.h"

Chunk::Chunk(vec3 _position, Scene* _scene) : position(_position), scene(_scene)
{
	for (int x = 0; x < CHUNK_SIZE; x++)
	{
		for (int y = 0; y < CHUNK_SIZE; y++)
		{
			for (int z = 0; z < CHUNK_SIZE; z++)
			{
				// Load blocks ids by scene height map
				// Resuse GetHeight values ?
				if (y <= scene->heightMap.GetColumnHeight(vec3(x,y,z) * position))
					blocks.push_back(1);
				else
					blocks.push_back(0);
			}
		}
	}
}

void Chunk::SetBlock(vec3 blockPosition, unsigned short blockId)
{
	blocks[GetBlockIndex(blockPosition)] = blockId;
	Update();
}

void Chunk::Update()
{
	float startTime = (float)glfwGetTime();
	vector<Vertex> vertices;
	
	// For each blocks of the chunk
	unsigned short int blockChunkId = 0;
	for (int x = 0; x < CHUNK_SIZE; x++)
	{
		for (int y = 0; y < CHUNK_SIZE; y++)
		{
			for (int z = 0; z < CHUNK_SIZE; z++)
			{
				// Create visible faces
				if (blocks[blockChunkId] != 0)
				{
					vector<Vertex> blockFaces = CreateBlockMesh(vec3(x, y, z));
					if (blockFaces.size() > 0)
					{
						vertices.insert(vertices.end(), blockFaces.begin(), blockFaces.end());
					}
				}
				blockChunkId++;
			}
		}
	}

	if (vertices.size() > 0)
	{
		mesh.Load(vertices);
		//cout << "Chunk generation duration : " << ((float)glfwGetTime() - startTime) << endl;
	}
}

vector<Vertex> Chunk::CreateBlockMesh(vec3 blockPosition)
{
	vector<Vertex> vertices;

	// Top face
	if (GetBlockType(vec3(blockPosition.x, blockPosition.y + 1, blockPosition.z)) == 0)
		vertices.insert(vertices.end(), Renderer::topFace.begin(), Renderer::topFace.end());
	// Bottom face
	if (GetBlockType(vec3(blockPosition.x, blockPosition.y - 1, blockPosition.z)) == 0)
		vertices.insert(vertices.end(), Renderer::bottomFace.begin(), Renderer::bottomFace.end());

	// Right face
	if (GetBlockType(vec3(blockPosition.x + 1, blockPosition.y, blockPosition.z)) == 0)
		vertices.insert(vertices.end(), Renderer::rightFace.begin(), Renderer::rightFace.end());
	// Left face
	if (GetBlockType(vec3(blockPosition.x - 1, blockPosition.y, blockPosition.z)) == 0)
		vertices.insert(vertices.end(), Renderer::leftFace.begin(), Renderer::leftFace.end());

	// Front face
	if (GetBlockType(vec3(blockPosition.x, blockPosition.y, blockPosition.z - 1)) == 0)
		vertices.insert(vertices.end(), Renderer::frontFace.begin(), Renderer::frontFace.end());
	// Back face
	if (GetBlockType(vec3(blockPosition.x, blockPosition.y, blockPosition.z + 1)) == 0)
		vertices.insert(vertices.end(), Renderer::backFace.begin(), Renderer::backFace.end());


	for (int i = 0; i < vertices.size(); i++)
	{
		vertices[i].position += vec3(blockPosition.x * BLOCK_SIZE, blockPosition.y * BLOCK_SIZE, blockPosition.z * BLOCK_SIZE);
	}

	return vertices;
}

void Chunk::Draw()
{
	Renderer::Draw(mesh, Renderer::defaultShader, position);
}

unsigned short Chunk::GetBlockType(short int blockChunkId)
{
	if (blockChunkId < 0 || blockChunkId >= blocks.size())
		return 0;

	return blocks[blockChunkId];
}

unsigned short Chunk::GetBlockType(vec3 blockPosition)
{
	if (blockPosition.x >= 0 && blockPosition.x < CHUNK_SIZE)
	{
		if (blockPosition.y >= 0 && blockPosition.y < CHUNK_SIZE)
		{
			if (blockPosition.z >= 0 && blockPosition.z < CHUNK_SIZE)
			{
				int index = ((CHUNK_SIZE * CHUNK_SIZE) * blockPosition.x) + (CHUNK_SIZE * blockPosition.y) + blockPosition.z;
				if (index >= 0 && index < blocks.size())
				{
					return blocks[index];
				}
			}
		}
	}
	return 0;

}

unsigned short Chunk::GetBlockIndex(vec3 blockPosition)
{
	if (blockPosition.x >= 0 && blockPosition.x < CHUNK_SIZE)
	{
		if (blockPosition.y >= 0 && blockPosition.y < CHUNK_SIZE)
		{
			if (blockPosition.z >= 0 && blockPosition.z < CHUNK_SIZE)
			{
				return ((CHUNK_SIZE * CHUNK_SIZE) * blockPosition.x) + (CHUNK_SIZE * blockPosition.y) + blockPosition.z;
			}
		}
	}
	return 0;
}
