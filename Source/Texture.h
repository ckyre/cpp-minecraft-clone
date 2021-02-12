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
		GLuint GetId();
		int GetSize();
		int GetWidth();
		int GetHeight();
	private:
		unsigned char* Load(const char* path);
		GLuint id;
		int width, height, size;
		unsigned char* data;
};

