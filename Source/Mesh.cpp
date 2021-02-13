#include "Mesh.h"

Mesh::Mesh(const char* path)
{
	Load(path);
}

bool Mesh::Load(const char* path)
{
	Assimp::Importer importer();
	const aiScene* pScene = Assimp::Importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);

	return true;
}

vector<vec3> Mesh::GetVerticesPositions() { return positions; }
vector<vec3> Mesh::GetVerticesUVs() { return uvs; }
vector<vec3> Mesh::GetVerticesNormals() { return normals; }
