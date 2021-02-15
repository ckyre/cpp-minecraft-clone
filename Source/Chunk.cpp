#include "Chunk.h"

Chunk::Chunk(Scene _parentScene, vec3 _position) : parentScene(_parentScene), position(_position)
{
}

void Chunk::Update()
{
	blocks.resize(4096);
	for (int i = 0; i < 4096; i++)
	{
		blocks[i] = 1;
	}

	vector<Vertex> vertices;

	// For each blocks of the chunk
	unsigned short int blockChunkId = 0;
	for (int y = 0; y < 16; y++)
	{
		for (int x = 0; x < 16; x++)
		{
			for (int z = 0; z < 16; z++)
			{
				// Create visible faces
				if (blocks[blockChunkId] != 0)
				{
					vector<Vertex> blockFaces = CreateBlockMesh(blockChunkId);
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
	}
}

vector<Vertex> Chunk::CreateBlockMesh(unsigned short int blockChunkId)
{
	vector<Vertex> vertices;

	unsigned short int y = (blockChunkId / 256);
	unsigned short int x = (blockChunkId - (y * 256)) / 16;
	unsigned short int z = (blockChunkId - (y * 256)) % 16;

	// Top face
	if (GetBlock(blockChunkId + 256) == 0)
		vertices.insert(vertices.end(), Renderer::topFace.begin(), Renderer::topFace.end());
	// Bottom face
	if (GetBlock(blockChunkId - 256) == 0)
		vertices.insert(vertices.end(), Renderer::bottomFace.begin(), Renderer::bottomFace.end());

	// Right face
	if (GetBlock(blockChunkId + 16) == 0 || x == 15)
		vertices.insert(vertices.end(), Renderer::rightFace.begin(), Renderer::rightFace.end());
	// Left face
	if (GetBlock(blockChunkId - 16) == 0 || x == 0)
		vertices.insert(vertices.end(), Renderer::leftFace.begin(), Renderer::leftFace.end());

	// Front face
	if (GetBlock(blockChunkId - 1) == 0 || z == 0)
		vertices.insert(vertices.end(), Renderer::frontFace.begin(), Renderer::frontFace.end());
	// Back face
	if (GetBlock(blockChunkId + 1) == 0 || z == 15)
		vertices.insert(vertices.end(), Renderer::backFace.begin(), Renderer::backFace.end());

	for (int i = 0; i < vertices.size(); i++)
	{
		vertices[i].position += vec3(x * 2, y * 2, z * 2);
	}

	return vertices;
}

void Chunk::Draw()
{
	Renderer::Draw(mesh, Renderer::defaultShader, position);
}

unsigned short Chunk::GetBlock(short int blockChunkId)
{
	if (blockChunkId < 0 || blockChunkId >= blocks.size())
	{
		return 0;
	}
	else
	{
		return blocks[blockChunkId];
	}
}

unsigned short Chunk::GetBlock(vec3 position)
{
	if (position.y >= 0 && position.y <= 15)
	{
		if (position.x >= 0 && position.x <= 15)
		{
			if (position.z >= 0 && position.z <= 15)
			{
				int index = (256 * position.y) + (16 * position.x) + position.z;
				if (index >= 0 || index < blocks.size())
				{
					return blocks[index];
				}
			}
		}
	}
	return 0;

}
