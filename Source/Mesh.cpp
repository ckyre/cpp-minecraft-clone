#include "Mesh.h"

Mesh::Mesh()
{
}

void Mesh::Load(const char* path)
{
	// Load file
	vector<Vertex> vertices;
	Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);
	if (scene)
	{
		// Foeach meshs in scene
		for (unsigned int i = 0; i < scene->mNumMeshes; i++)
		{
			const aiMesh* mesh = scene->mMeshes[i];
			const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

			// Foreach vertices in mesh
			for (unsigned int j = 0; j < mesh->mNumVertices; j++)
			{
				const aiVector3D* _positions = &(mesh->mVertices[j]);
				const aiVector3D* _normals = &(mesh->mNormals[j]);
				const aiVector3D* _uvs = mesh->HasTextureCoords(0) ? &(mesh->mTextureCoords[0][j]) : &Zero3D;

				Vertex vertex;
				vertex.position.x = (float)_positions->x;
				vertex.position.y = (float)_positions->y;
				vertex.position.z = (float)_positions->z;
				vertex.uvs.x = (float)_uvs->x;
				vertex.uvs.y = (float)_uvs->y;
				vertex.normals.x = (float)_normals->x;
				vertex.normals.y = (float)_normals->y;
				vertex.normals.z = (float)_normals->z;
				vertices.push_back(vertex);
			}
		}
	}
	
	IndexVertexBuffer(vertices);
}

void Mesh::Load(vector<Vertex> vertices)
{
	IndexVertexBuffer(vertices);
}

void Mesh::IndexVertexBuffer(vector<Vertex> vertices)
{
	vector<Vertex> outVertices;
	vector<unsigned short> outIndices;
	map<Vertex, unsigned short> indexer;

	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		unsigned short index;
		bool found = ContainVertex(vertices[i], indexer, index);
		if (found)
		{
			outIndices.push_back(index);
		}
		else
		{
			outVertices.push_back(vertices[i]);
			unsigned short newIndex = (unsigned short)outVertices.size() - 1;
			outIndices.push_back(newIndex);
			indexer[vertices[i]] = newIndex;
		}
	}

	vb.Fill(outVertices);
	ib.Fill(outIndices);
}

bool Mesh::ContainVertex(Vertex vertex, map<Vertex, unsigned short> &indexer, unsigned short &index)
{
	std::map<Vertex, unsigned short>::iterator iterator = indexer.find(vertex);
	if (iterator == indexer.end())
	{
		return false;
	}
	else
	{
		index = iterator->second;
		return true;
	}
	return false;
}

int Mesh::GetVertexBufferSize() { return vb.GetSize(); }
int Mesh::GetIndexBufferSize() { return ib.GetSize(); }
int Mesh::GetVertexBufferCount() { return vb.GetCount(); }
int Mesh::GetIndexBufferCount() { return ib.GetCount(); }

void Mesh::Bind()
{
	vb.Bind();
	ib.Bind();
}

void Mesh::Unbind()
{
	vb.Unbind();
	ib.Unbind();
}
