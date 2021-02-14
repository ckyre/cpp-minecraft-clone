#include <vector>
using namespace std;
#include <GL/glew.h>

#pragma once
class IndexBuffer
{
	private:
		unsigned int id;
		unsigned int size;
		unsigned int count;

	public:
		IndexBuffer();
		void Fill(vector<unsigned short> indices);
		int GetSize();
		int GetCount();

		void Bind();
		void Unbind();
};

