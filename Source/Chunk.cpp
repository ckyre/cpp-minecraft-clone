#include "Chunk.h"
#include "Renderer.h"

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
				if (blockChunkId < blocks.size())
				{
					// Create visible faces
					if (blocks[blockChunkId] != 0)
					{
						vector<Vertex> blockFaces = CreateBlock(blockChunkId);
						if (blockFaces.size() > 0)
							vertices.insert(vertices.end(), blockFaces.begin(), blockFaces.end());

					}
					blockChunkId++;
				}
			}
		}
	}

	if (vertices.size() > 0)
	{
		mesh.Load(vertices);
	}
}

vector<Vertex> Chunk::CreateBlock(unsigned short int blockChunkId)
{
	vector<Vertex> vertices;

	unsigned short int y = (blockChunkId / 256);
	unsigned short int x = (blockChunkId - (y * 256)) / 16;
	unsigned short int z = (blockChunkId - (y * 256)) % 16;

	// Top face
	if (GetBlock(blockChunkId + 256) == 0)
	{
		vector<Vertex> face = Mesh::LoadFile("E:/Documents/Projets/Programmes/opengl/cpp-minecraft-clone/Assets/Meshes/top-face.obj");
		vertices.insert(vertices.end(), face.begin(), face.end());
	}
	// Bottom face
	if (GetBlock(blockChunkId - 256) == 0)
	{
		vector<Vertex> face = Mesh::LoadFile("E:/Documents/Projets/Programmes/opengl/cpp-minecraft-clone/Assets/Meshes/bottom-face.obj");
		vertices.insert(vertices.end(), face.begin(), face.end());
	}

	// Right face
	if (GetBlock(blockChunkId + 16) == 0 || x == 15)
	{
		vector<Vertex> face = Mesh::LoadFile("E:/Documents/Projets/Programmes/opengl/cpp-minecraft-clone/Assets/Meshes/right-face.obj");
		vertices.insert(vertices.end(), face.begin(), face.end());
	}
	// Left face
	if (GetBlock(blockChunkId - 16) == 0 || x == 0)
	{
		vector<Vertex> face = Mesh::LoadFile("E:/Documents/Projets/Programmes/opengl/cpp-minecraft-clone/Assets/Meshes/left-face.obj");
		vertices.insert(vertices.end(), face.begin(), face.end());
	}

	// Front face
	if (GetBlock(blockChunkId - 1) == 0 || z == 0)
	{
		vector<Vertex> face = Mesh::LoadFile("E:/Documents/Projets/Programmes/opengl/cpp-minecraft-clone/Assets/Meshes/front-face.obj");
		vertices.insert(vertices.end(), face.begin(), face.end());
	}
	// Back face
	if (GetBlock(blockChunkId + 1) == 0 || z == 15)
	{
		vector<Vertex> face = Mesh::LoadFile("E:/Documents/Projets/Programmes/opengl/cpp-minecraft-clone/Assets/Meshes/back-face.obj");
		vertices.insert(vertices.end(), face.begin(), face.end());
	}

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
