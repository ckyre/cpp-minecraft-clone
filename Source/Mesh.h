#include <vector>
using namespace std;
#include <GL/glew.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
using namespace Assimp;
#include <glm/glm.hpp>
using namespace glm;
#include "Vertex.h"
#include "VertexBuffer.h"

#pragma once
class Mesh
{
	private:
		VertexBuffer vb;
		//IndexBuffer ib;
	public:
		Mesh();
		void Load(const char* path);
		void Load(vector<Vertex> vertices);
		int GetSize();

		void Bind();
		void Unbind();
};

