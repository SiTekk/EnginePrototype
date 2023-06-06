#include "Backend.h"

#include <iostream>

namespace EnginePrototype::Backend
{
    GLFWwindow* g_window = nullptr;

    int Initialize()
    {
        if (glfwInit() == GLFW_FALSE)
        {
            std::cout << "Failed to initialize GLFW" << std::endl;

            return -1;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        g_window = glfwCreateWindow(1600, 900, "EnginePrototype", NULL, NULL);
        if (g_window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return -1;
        }

        glfwMakeContextCurrent(g_window);

        // TODO: Enable VSync for developement
        glfwSwapInterval(1);

        return 0;
    }

    int Cleanup()
    {
        glfwDestroyWindow(g_window);
        glfwTerminate();

        return 0;
    }
}
