#include <iostream>
using namespace std;
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
using namespace glm;
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "Time.h"

#pragma once
class Renderer
{
	private:
		static bool openglReady;
		static Camera camera;

	public:
		static GLFWwindow* window;
		static GLFWmonitor* monitor;
		static int windowWidth, windowHeight, monitorWidth, monitorHeight;

		static void PrepareOpenGL();
		static void CreateWindow(int width, int height, const char* title);

		static void Clear();
		static void Draw(Mesh mesh, Shader shader);
		static mat4 CalculateMVP();
};