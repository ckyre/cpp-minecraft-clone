#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#pragma once
class VertexBufferComponent
{
	public:
		unsigned int type;
		unsigned int count;
		unsigned char normalized;

		VertexBufferComponent(unsigned int _type, unsigned int _count, unsigned char _normalized)
		{
			type = _type;
			count = _count;
			normalized = _normalized;
		}

		static unsigned int GetSizeOfType(unsigned int type)
		{
			switch (type)
			{
				case GL_FLOAT: return 4;
				case GL_UNSIGNED_INT: return 4;
				case GL_UNSIGNED_BYTE: return 1;
			}
			return 0;
		}
};

class VertexBufferLayout
{
	private:
		std::vector<VertexBufferComponent> components;
		unsigned int stride;

	public:
		static std::vector<VertexBufferComponent> defaultLayout;

		VertexBufferLayout()
		{
			components = defaultLayout;
			stride = 0;
			for (int i = 0; i < defaultLayout.size(); i++)
			{
				stride += VertexBufferComponent::GetSizeOfType(defaultLayout[i].type) * defaultLayout[i].count;
			}
		}

		inline const std::vector<VertexBufferComponent> GetComponents() const { return components; }
		inline unsigned int GetStride() const { return stride; }

		template<typename T>
		void Push(unsigned int count)
		{
			static_assert(false);
		}

		template<>
		void Push<float>(unsigned int count)
		{
			components.push_back(VertexBufferComponent(GL_FLOAT, count, GL_FALSE));
			stride += count * VertexBufferComponent::GetSizeOfType(GL_FLOAT);
		}

		template<>
		void Push<unsigned int>(unsigned int count)
		{
			components.push_back(VertexBufferComponent(GL_UNSIGNED_INT, count, GL_FALSE));
			stride += count * VertexBufferComponent::GetSizeOfType(GL_UNSIGNED_INT);
		}

		template<>
		void Push<unsigned char>(unsigned int count)
		{
			components.push_back(VertexBufferComponent(GL_UNSIGNED_BYTE, count, GL_TRUE));
			stride += count * VertexBufferComponent::GetSizeOfType(GL_UNSIGNED_BYTE);
		}
};