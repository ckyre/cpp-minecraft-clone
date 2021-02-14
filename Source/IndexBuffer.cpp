#include "IndexBuffer.h"

IndexBuffer::IndexBuffer() : id(0), size(0)
{
}

void IndexBuffer::Fill(vector<unsigned short> indices)
{
	glGenBuffers(1, &id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);

	count = indices.size();
	size = indices.size() * sizeof(unsigned short);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, &indices[0], GL_STATIC_DRAW);
}

int IndexBuffer::GetSize() { return size; }

int IndexBuffer::GetCount() { return count; }

void IndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void IndexBuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
