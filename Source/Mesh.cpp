#include "Mesh.h"

Mesh::Mesh(const char* path)
{
	Load(path);
}

bool Mesh::Load(const char* path)
{
	Clear();

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
			for (unsigned int i = 0; i < mesh->mNumVertices; i++)
			{
				const aiVector3D* _positions = &(mesh->mVertices[i]);
				const aiVector3D* _normals = &(mesh->mNormals[i]);
				const aiVector3D* _uvs = mesh->HasTextureCoords(0) ? &(mesh->mTextureCoords[0][i]) : &Zero3D;

				positions.push_back(vec3((float)_positions->x, (float)_positions->y, (float)_positions->z));
				uvs.push_back(vec3((float)_uvs->x, (float)_uvs->y, (float)_uvs->z));
				uvs.push_back(vec3((float)_normals->x, (float)_normals->y, (float)_normals->z));

			}
		}
	}

	return true;
}

void Mesh::Clear()
{
	positions.clear();
	uvs.clear();
	normals.clear();
}

vector<vec3> Mesh::GetVerticesPositions() { return positions; }
vector<vec3> Mesh::GetVerticesUVs() { return uvs; }
vector<vec3> Mesh::GetVerticesNormals() { return normals; }
