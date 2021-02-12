#include "Buffer.h"

Buffer::Buffer()
{
	Create();
}

Buffer::Buffer(const GLfloat data[], const int dataSize)
{
	Create();
	Fill(data, dataSize);
}

void Buffer::Create()
{
	size = 0;
	glGenBuffers(1, &id);
}

void Buffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, id);
}

void Buffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Buffer::Fill(const GLfloat data[], const int dataSize)
{
	Bind();
	size = dataSize;
	glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
}

GLuint Buffer::GetId() { return id; }
int Buffer::GetSize() { return size; }
