#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <vector>
using namespace std;
#include "Renderer.h"
#include "Time.h"
#include "Mesh.h"
#include "VertexBufferLayout.h"
#include "Chunk.h"

int main()
{
    // Initialization
    Renderer::PrepareOpenGL();
    Renderer::CreateWindow(1024, 768, "Minecraft clone");

    Renderer::LoadDefaultResources();

    //Chunk chunk;
    //chunk.Start();

    // Main loop
    while (glfwGetKey(Renderer::window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(Renderer::window) == 0)
    {
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		Time::Update();
		Renderer::Clear();

        //chunk.Update();
        Renderer::Draw(Renderer::cubeMesh, Renderer::defaultShader, vec3(0, 0, -10));

		// Swap buffers
		glfwSwapBuffers(Renderer::window);
		glfwPollEvents();
    }

    return 0;
}
