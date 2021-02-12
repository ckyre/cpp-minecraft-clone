#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
using namespace glm;

#pragma once
class Renderer
{
	public:
		GLFWwindow* window;

		void CreateWindow(int width, int height, const char* title);
		void Start();
		void Update();
		void End();
};

