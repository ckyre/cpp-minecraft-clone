#include <iostream>
using namespace std;
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
using namespace glm;
#pragma once

//https://www.reddit.com/r/webgl/comments/37rb43/should_i_create_a_new_buffer_for_everything/crp6n2h?utm_source=share&utm_medium=web2x&context=3

class Buffer
{
	public:
		Buffer();
		Buffer(const GLfloat data[], const int dataSize);
		void Bind();
		void Unbind();
		void Fill(const GLfloat data[], const int dataSize);
		GLuint GetId();
		int GetSize();
	private:
		void Create();
		GLuint id;
		int size;
};

