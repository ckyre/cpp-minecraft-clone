#include <iostream>

#include <vector>
using namespace std;
#include <GL/glew.h>
#include "Vertex.h"

#pragma once
class VertexBuffer
{
	private:
		unsigned int id;
		unsigned int size;
	public:
		VertexBuffer();
		void Fill(vector<Vertex> vertices);
		int GetSize();

		void Bind();
		void Unbind();
};

