#include <vector>
#include <map>
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
#include "IndexBuffer.h"

#pragma once
class Mesh
{
	private:
		VertexBuffer vb;
		IndexBuffer ib;

		void IndexVertexBuffer(vector<Vertex> vertices);
		bool ContainVertex(Vertex vertex, map<Vertex, unsigned short> &indexer, unsigned short &index);
	public:
		Mesh();
		void Load(const char* path);
		void Load(vector<Vertex> vertices);
		int GetVertexBufferSize();
		int GetIndexBufferSize();
		int GetVertexBufferCount();
		int GetIndexBufferCount();

		void Bind();
		void Unbind();
};

