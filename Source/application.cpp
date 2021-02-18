#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <vector>
using namespace std;
#include "Renderer.h"
#include "Time.h"
#include "Mesh.h"
#include "Camera.h"
#include "Random.h"

int main()
{
    // Initialization
    Random::Start();

    Renderer::PrepareOpenGL();
    Renderer::CreateWindow(1024, 768, "Minecraft clone");

    Renderer::LoadDefaultResources();

    Scene scene;
    scene.Start();

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
