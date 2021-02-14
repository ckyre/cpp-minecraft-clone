#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;
#include <GL/glew.h>
#include <glm/glm.hpp>
using namespace glm;
#include "Texture.h"

#pragma once
enum class ShaderType { VERTEX, FRAGMENT };

class Shader
{
	private:
		unsigned int id; // Program id
		Texture texture;

		GLuint CompileShader(ShaderType type, const char* path);
	public:
		Shader();
		void Load(const char* vertexShaderPath, const char* fragmentShaderPath);

		void UniformTexture(Texture texture);
		void UniformMatrix4fv(const char* uniform, mat4 matrix);

		void Bind();
		int GetId();
};

