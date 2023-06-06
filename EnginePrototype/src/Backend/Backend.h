#ifndef BACKEND_H
#define BACKEND_H

#include <GLFW/glfw3.h>

namespace EnginePrototype::Backend
{
    int Initialize();
    int Cleanup();

    extern GLFWwindow* g_window;
}


#endif //BACKEND_H