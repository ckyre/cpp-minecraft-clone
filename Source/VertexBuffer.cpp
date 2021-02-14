#include "VertexBuffer.h"

VertexBuffer::VertexBuffer() : id(0), size(0)
{
}

void VertexBuffer::Fill(vector<Vertex> vertices)
{
	// Create buffer
	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);

	// Convert Vertex vector to float vector
	vector<float> floatVertices;
	for (Vertex vertex : vertices)
	{
		vector<float> floatVertex = vertex.ToArray();
		floatVertices.insert(floatVertices.end(), floatVertex.begin(), floatVertex.end());
	}

	// Send data to buffer
	size = floatVertices.size() * sizeof(float);
	glBufferData(GL_ARRAY_BUFFER, size, floatVertices.data(), GL_STATIC_DRAW);
}

int VertexBuffer::GetSize()
{
	return size;
}

void VertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VertexBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
