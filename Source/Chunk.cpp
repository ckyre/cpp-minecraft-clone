#include "Chunk.h"
#include "Renderer.h"

void Chunk::Start()
{
	for (int i = 0; i < 4096; i++)
	{
		if ((i > (4096 / 2) - 50))
			blocks.push_back(0);
		else
			blocks.push_back(1);
	}
}

void Chunk::Update()
{
	vector<Vertex> vertices;


	// For each block of the chunk
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
					vector<Vertex> blockFaces = CreateBlock(vec3(x, y, z));
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
		cout << vertices.size() << endl;
		mesh.Load(vertices);
	}
}

void Chunk::Draw()
{
	Renderer::Draw(mesh, Renderer::defaultShader, vec3(0, 0, 0));
}

vector<Vertex> Chunk::CreateBlock(vec3 blockLocalPosition)
{
	vector<Vertex> vertices;

	// Top face
	if (GetBlock(vec3(blockLocalPosition.x, blockLocalPosition.y + 1, blockLocalPosition.z)) == 0)
	{
		vector<Vertex> face = Mesh::LoadFile("E:/Documents/Projets/Programmes/opengl/cpp-minecraft-clone/Assets/Meshes/top-face.obj");
		vertices.insert(vertices.end(), face.begin(), face.end());
	}
	// Bottom face
	if (GetBlock(vec3(blockLocalPosition.x, blockLocalPosition.y - 1, blockLocalPosition.z)) == 0)
	{
		vector<Vertex> face = Mesh::LoadFile("E:/Documents/Projets/Programmes/opengl/cpp-minecraft-clone/Assets/Meshes/bottom-face.obj");
		vertices.insert(vertices.end(), face.begin(), face.end());
	}
	// Right face
	if (GetBlock(vec3(blockLocalPosition.x + 1, blockLocalPosition.y, blockLocalPosition.z)) == 0)
	{
		vector<Vertex> face = Mesh::LoadFile("E:/Documents/Projets/Programmes/opengl/cpp-minecraft-clone/Assets/Meshes/right-face.obj");
		vertices.insert(vertices.end(), face.begin(), face.end());
	}
	// Left face
	if (GetBlock(vec3(blockLocalPosition.x - 1, blockLocalPosition.y, blockLocalPosition.z)) == 0)
	{
		vector<Vertex> face = Mesh::LoadFile("E:/Documents/Projets/Programmes/opengl/cpp-minecraft-clone/Assets/Meshes/left-face.obj");
		vertices.insert(vertices.end(), face.begin(), face.end());
	}
	// Front face
	if (GetBlock(vec3(blockLocalPosition.x, blockLocalPosition.y, blockLocalPosition.z - 1)) == 0)
	{
		vector<Vertex> face = Mesh::LoadFile("E:/Documents/Projets/Programmes/opengl/cpp-minecraft-clone/Assets/Meshes/front-face.obj");
		vertices.insert(vertices.end(), face.begin(), face.end());
	}
	// Back face
	if (GetBlock(vec3(blockLocalPosition.x, blockLocalPosition.y, blockLocalPosition.z + 1)) == 0)
	{
		vector<Vertex> face = Mesh::LoadFile("E:/Documents/Projets/Programmes/opengl/cpp-minecraft-clone/Assets/Meshes/back-face.obj");
		vertices.insert(vertices.end(), face.begin(), face.end());
	}

	for (int i = 0; i < vertices.size(); i++)
	{
		vertices[i].position += vec3(blockLocalPosition.x * 2, blockLocalPosition.y * 2, blockLocalPosition.z * 2);
	}

	return vertices;
}

unsigned short Chunk::GetBlock(short int blockChunkId)
{
	if (blockChunkId < 0 || blockChunkId > blocks.size())
		return 0;
	else
		return blocks[blockChunkId];
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
				return blocks[index];
			}
		}
	}
	return 0;

}
