#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std;

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
using namespace glm;

#include "Renderer.h";

int main()
{
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    static Renderer renderer;
    renderer.CreateWindow(1024, 768, "Minecraft clone");
    renderer.Start();

    // Créer un contexte OpenGL
    glfwMakeContextCurrent(renderer.window);
    glewExperimental = true;
    if (glewInit() != GLEW_OK)
    {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }

    // Assure que l'on peut capturer la touche d'échappement enfoncée ci-dessous
    glfwSetInputMode(renderer.window, GLFW_STICKY_KEYS, GL_TRUE);

    // Boucle principale
    while (glfwGetKey(renderer.window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(renderer.window) == 0)
    {
        renderer.Update();

        // Swap buffers
        glfwSwapBuffers(renderer.window);
        glfwPollEvents();
    }

    renderer.End();

    return 0;
}