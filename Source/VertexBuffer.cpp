#include "VertexBuffer.h"

VertexBuffer::VertexBuffer() : id(0), size(0)
{
}

void VertexBuffer::Fill(vector<Vertex> vertices)
{
	// Create buffer
	glGenBuffers(1, &id);
	Bind();

	// Convert Vertex vector to float vector
	vector<float> floatVertices;
	for (Vertex vertex : vertices)
	{
		vector<float> floatVertex = vertex.ToArray();
		floatVertices.insert(floatVertices.end(), floatVertex.begin(), floatVertex.end());
	}

	// Send data to buffer
	count = floatVertices.size();
	size = floatVertices.size() * sizeof(float);
	glBufferData(GL_ARRAY_BUFFER, size, floatVertices.data(), GL_STATIC_DRAW);
}

int VertexBuffer::GetSize() { return size; }
int VertexBuffer::GetCount() { return count; }

void VertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, id);

	// Bind layout
	vector<VertexBufferComponent> components = layout.GetComponents();
	int offset = 0;
	for (int i = 0; i < components.size(); i++)
	{
		VertexBufferComponent component = components[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, component.count, component.type, component.normalized, layout.GetStride(), (void*)offset);
		offset += VertexBufferComponent::GetSizeOfType(component.type) * component.count;
	}
}
void VertexBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
