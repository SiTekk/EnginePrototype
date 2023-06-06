#ifndef RENDERER_H
#define RENDERER_H

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace EnginePrototype::Renderer
{
    void RenderFrame();

    int Initialize();
    int Cleanup();

    struct Vertex
    {
        glm::vec3 pos;
        glm::vec3 color;
    };
}

#endif //RENDERER_H