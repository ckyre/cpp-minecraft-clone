#include "Chunk.h"
#include "Renderer.h"

void Chunk::Start()
{
	for (int i = 0; i < 4096; i++)
	{
		if (i < (4096 / 2) - 50)
			data.push_back(1);
		else
			data.push_back(0);
	}

}

void Chunk::Update()
{
	vector<Vertex> vertices;
	int blockChunkId = 0;
	for (int y = 0; y < 16; y++)
	{
		for (int x = 0; x < 16; x++)
		{
			for (int z = 0; z < 16; z++)
			{
				// Prevent drawing unseen faces
				if (data[blockChunkId] != 0)
				{
					vector<Vertex> face = CreateBlock(vec3(x, y, z));
					vertices.insert(vertices.end(), face.begin(), face.end());
				}
				blockChunkId++;
			}
		}
	}
	Mesh chunkMesh;
	chunkMesh.Load(vertices);
	Renderer::Draw(chunkMesh, Renderer::defaultShader, vec3(0, 0, 0));
}

vector<Vertex> Chunk::CreateBlock(vec3 position)
{
	vector<Vertex> vertices;

	// Top face
	if (GetBlock(vec3(position.x, position.y + 1, position.z)) == 0)
	{
		vector<Vertex> face = Mesh::LoadFile("E:/Documents/Projets/Programmes/opengl/cpp-minecraft-clone/Assets/Meshes/face.obj");
		vertices.insert(vertices.end(), face.begin(), face.end());
	}
	/*
	// Bottom face
	if (GetBlock(vec3(position.x, position.y - 1, position.z)) == 0)
	{

	}

	// Right face
	if (GetBlock(vec3(position.x + 1, position.y, position.z)) == 0)
	{

	}

	// Left face
	if (GetBlock(vec3(position.x + 1, position.y, position.z)) == 0)
	{

	}

	// Front face
	if (GetBlock(vec3(position.x, position.y, position.z - 1)) == 0)
	{

	}

	// Back face
	if (GetBlock(vec3(position.x, position.y, position.z + 1)) == 0)
	{

	}
	*/
	return vertices;
}

unsigned short Chunk::GetBlock(int index)
{
	return data[index];
}

unsigned short Chunk::GetBlock(vec3 position)
{
	/*if (position.y >= 0 && position.y <= 15)
	{
		if (position.x >= 0 && position.x <= 15)
		{
			if (position.z >= 0 && position.z <= 15)
			{
				return (256 * position.y) + (16 * position.x) + position.z;
			}
		}
	}
	cout << "Error while getting bloc in chunk : wrong coordinates space";*/
	return (256 * position.y) + (16 * position.x) + position.z;

}
