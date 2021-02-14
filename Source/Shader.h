#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;
#include <GL/glew.h>

#pragma once
enum class ShaderType { VERTEX, FRAGMENT };

class Shader
{
	private:
		unsigned int id; // Program id

		GLuint CompileShader(ShaderType type, const char* path);
	public:
		Shader();
		void Load(const char* vertexShaderPath, const char* fragmentShaderPath);

		void Bind();
		int GetId();
};

