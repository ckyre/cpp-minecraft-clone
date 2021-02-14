#include <iostream>
#include <stdio.h>
using namespace std;
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "stb_image.h"
#pragma once

class Texture
{
	public:
		Texture();
		void Load(const char* path);

		void Bind();
		void Unbind();

	private:
		GLuint id;
		int width, height;
};

