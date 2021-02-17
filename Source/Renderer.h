#include <iostream>
using namespace std;
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
using namespace glm;
#include "Time.h"
#include "Scene.h"
#include "Mesh.h"
#include "Shader.h"

#pragma once
class Renderer;

class Renderer
{
	private:
		static bool openglReady;

	public:
		static GLFWwindow* window;
		static GLFWmonitor* monitor;
		static int windowWidth, windowHeight, monitorWidth, monitorHeight;

		static void PrepareOpenGL();
		static void CreateWindow(int width, int height, const char* title);
		static void LoadDefaultResources();

		static void Clear();
		static void Draw(Mesh mesh, Shader shader, vec3 position);

		// Default resources
		static Mesh defaultMesh;
		static Shader defaultShader;
		static vector<Vertex> topFace, bottomFace, frontFace, backFace, rightFace, leftFace;
};