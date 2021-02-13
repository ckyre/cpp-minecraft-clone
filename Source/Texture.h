#include <iostream>
#include <stdio.h>
using namespace std;
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include "stb_image.h"
#pragma once

class Texture
{
	public:
		Texture(const char* path);
		GLuint Bind();
		void Unbind();
		bool Load(const char* path);

		GLuint GetId();
		int GetSize();
		int GetWidth();
		int GetHeight();
	private:
		GLuint id;
		int width, height;
};

