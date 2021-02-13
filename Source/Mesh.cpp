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

				positions.push_back((float)_positions->x);
				positions.push_back((float)_positions->y);
				positions.push_back((float)_positions->z);
				uvs.push_back((float)_uvs->x);
				uvs.push_back((float)_uvs->y);
				//uvs.push_back((float)_uvs->z);
				normals.push_back((float)_normals->x);
				normals.push_back((float)_normals->y);
				normals.push_back((float)_normals->z);
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

GLfloat* Mesh::GetVerticesPositions()
{
	int size = positions.size();
	GLfloat* _positions = new GLfloat[size];
	copy(positions.begin(), positions.end(), _positions);
	return _positions;
}

GLfloat* Mesh::GetVerticesUVs()
{
	int size = uvs.size();
	GLfloat* _uvs = new GLfloat[size];
	copy(uvs.begin(), uvs.end(), _uvs);
	return _uvs;
}

GLfloat* Mesh::GetVerticesNormals()
{
	return nullptr;
}

int Mesh::GetPositionsCount()
{
	return positions.size();
}

int Mesh::GetUVsCount()
{
	return uvs.size();
}


