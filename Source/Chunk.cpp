#include "Chunk.h"
#include "Renderer.h"

Chunk::Chunk(vec3 _position) : position(_position)
{
	int size = (CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE);
	blocks.resize(size);
	for (int i = 0; i < size; i++)
	{
		blocks[i] = 1;
	}
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
		cout << "Chunk generation duration : " << ((float)glfwGetTime() - startTime) << endl;
	}
}

vector<Vertex> Chunk::CreateBlockMesh(vec3 blockPosition)
{
	vector<Vertex> vertices;

	// Top face
	if (GetBlockId(vec3(blockPosition.x, blockPosition.y + 1, blockPosition.z)) == 0)
		vertices.insert(vertices.end(), Renderer::topFace.begin(), Renderer::topFace.end());
	// Bottom face
	if (GetBlockId(vec3(blockPosition.x, blockPosition.y - 1, blockPosition.z)) == 0)
		vertices.insert(vertices.end(), Renderer::bottomFace.begin(), Renderer::bottomFace.end());

	// Right face
	if (GetBlockId(vec3(blockPosition.x + 1, blockPosition.y, blockPosition.z)) == 0)
		vertices.insert(vertices.end(), Renderer::rightFace.begin(), Renderer::rightFace.end());
	// Left face
	if (GetBlockId(vec3(blockPosition.x - 1, blockPosition.y, blockPosition.z)) == 0)
		vertices.insert(vertices.end(), Renderer::leftFace.begin(), Renderer::leftFace.end());

	// Front face
	if (GetBlockId(vec3(blockPosition.x, blockPosition.y, blockPosition.z - 1)) == 0)
		vertices.insert(vertices.end(), Renderer::frontFace.begin(), Renderer::frontFace.end());
	// Back face
	if (GetBlockId(vec3(blockPosition.x, blockPosition.y, blockPosition.z + 1)) == 0)
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

unsigned short Chunk::GetBlockId(short int blockChunkId)
{
	if (blockChunkId < 0 || blockChunkId >= blocks.size())
		return 0;

	return blocks[blockChunkId];
}

unsigned short Chunk::GetBlockId(vec3 blockPosition)
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
