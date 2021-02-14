#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <vector>
using namespace std;
#include "Renderer.h"
#include "Time.h"
#include "Mesh.h"
#include "VertexBufferLayout.h"

int main()
{
    // Initialization
    Renderer::PrepareOpenGL();
    Renderer::CreateWindow(1024, 768, "Minecraft clone");

	// VOA
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	Mesh mesh;
	mesh.Load("E:/Documents/Projets/Programmes/opengl/cpp-minecraft-clone/Assets/Meshes/sphere.obj");

    Shader shader;
    shader.Load("E:/Documents/Projets/Programmes/opengl/cpp-minecraft-clone/Source/Shaders/vDefault.glsl",
				"E:/Documents/Projets/Programmes/opengl/cpp-minecraft-clone/Source/Shaders/fDefault.glsl");

	Texture texture;
	texture.Load("E:/Documents/Projets/Programmes/opengl/cpp-minecraft-clone/Assets/Textures/bricks.bmp");
	shader.UniformTexture(texture);

    // Main loop
    while (glfwGetKey(Renderer::window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(Renderer::window) == 0)
    {
		Time::Update();
		Renderer::Clear();

		Renderer::Draw(mesh, shader);

		// Swap buffers
		glfwSwapBuffers(Renderer::window);
		glfwPollEvents();
    }

    return 0;
}

vector<VertexBufferComponent> VertexBufferLayout::defaultLayout;
