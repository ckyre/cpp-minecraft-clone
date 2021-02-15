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

    Scene scene;
    scene.GenerateWorld();
    
    // Main loop
    while (glfwGetKey(Renderer::window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(Renderer::window) == 0)
    {
		Time::Update();
		Renderer::Clear();

        scene.Update();

		// Swap buffers
		glfwSwapBuffers(Renderer::window);
		glfwPollEvents();
    }

    return 0;
}
