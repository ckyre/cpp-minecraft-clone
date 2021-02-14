#include <iostream>
#include <vector>
using namespace std;
#include <GL/glew.h>
#include "Vertex.h"
#include "VertexBufferLayout.h"

#pragma once
class VertexBuffer
{
	private:
		unsigned int id;
		unsigned int size;
		VertexBufferLayout layout;

	public:
		VertexBuffer();
		void Fill(vector<Vertex> vertices);
		int GetSize();

		void Bind();
		void Unbind();
};

