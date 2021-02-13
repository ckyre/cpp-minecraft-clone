#include <stdio.h>
#include <stdlib.h>
#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <string>
using namespace std;
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
using namespace glm;
#include "Renderer.h"

int main()
{
    // Initalise GLFW
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    Renderer::CreateWindow(1024, 768, "Minecraft clone");

    // Créer un contexte OpenGL
    glfwMakeContextCurrent(Renderer::window);

    // Initalise GLEW
    glewExperimental = true;
    if (glewInit() != GLEW_OK)
    {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }

    Renderer::Start();

    // Boucle principale
    while (glfwGetKey(Renderer::window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(Renderer::window) == 0)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Renderer::Update();

        // Swap buffers
        glfwSwapBuffers(Renderer::window);
        glfwPollEvents();
    }

    Renderer::End();

    return 0;
}