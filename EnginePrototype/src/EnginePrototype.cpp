#include "EnginePrototype.h"

#include <iostream>

#include "Backend/Backend.h"
#include "Renderer/Renderer.h"

namespace EnginePrototype
{
    void handleInputs(GLFWwindow* window)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }

    int mainLoop()
    {
        while (!glfwWindowShouldClose(Backend::g_window))
        {
            glfwPollEvents();
            
            handleInputs(Backend::g_window);

            Renderer::RenderFrame();

            glfwSwapBuffers(Backend::g_window);
        }

        return 0;
    }

    int Run()
    {
        if (Backend::Initialize() == -1)
            return -1;

        if (Renderer::Initialize() == -1)
            return -1;

        mainLoop();

        Renderer::Cleanup();

        Backend::Cleanup();

        return 0;
    }
}
