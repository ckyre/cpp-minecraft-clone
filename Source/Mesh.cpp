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
				//vertex.normals.x = (float)_normals->x;
				//vertex.normals.y = (float)_normals->y;
				//vertex.normals.z = (float)_normals->z;
				vertices.push_back(vertex);
			}
		}
	}
	vb.Fill(vertices);
}

void Mesh::Load(vector<Vertex> vertices)
{
	vb.Fill(vertices);
}

int Mesh::GetSize()
{
	return vb.GetSize();
}

void Mesh::Bind()
{
	vb.Bind();
	//ib.Bind();
}

void Mesh::Unbind()
{
	vb.Unbind();
	//ib.Unbind();
}
