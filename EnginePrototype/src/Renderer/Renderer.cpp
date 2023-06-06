#include "Renderer.h"

#include <iostream>
#include <vector>
#include <fstream>

#include <glad/gl.h>

#include "../Backend/Backend.h"

namespace EnginePrototype::Renderer
{
    static const std::vector<Vertex> vertices =
    {
        {{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}},
        {{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}},
        {{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}},
        {{-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}}
    };

    const GLuint indices[] = 
    {
        0, 1, 2, 2, 3, 0
    };

    GLuint shaderProgram;

    GLuint vertexArray;
    GLuint vertexBuffer;

    GLuint elementBuffer;

    GLuint uniformBuffer;

    int readFile(const std::string& filename, std::vector<char>& buffer);

    int createShaders()
    {
        GLuint vertexShader;
        GLuint fragmentShader;

        {
            std::vector<char> shaderCodeVert, shaderCodeFrag;

            if (readFile("shader/vert.spv", shaderCodeVert) == -1)
                return -1;

            if (readFile("shader/frag.spv", shaderCodeFrag) == -1)
                return -1;

            vertexShader = glCreateShader(GL_VERTEX_SHADER);
            fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

            glShaderBinary(1, &vertexShader, GL_SHADER_BINARY_FORMAT_SPIR_V, shaderCodeVert.data(), static_cast<GLsizei>(shaderCodeVert.size()));
            glShaderBinary(1, &fragmentShader, GL_SHADER_BINARY_FORMAT_SPIR_V, shaderCodeFrag.data(), static_cast<GLsizei>(shaderCodeFrag.size()));

            glSpecializeShader(vertexShader, "main", 0, nullptr, nullptr);
            glSpecializeShader(fragmentShader, "main", 0, nullptr, nullptr);
        }

        // Check if the shaders are successfully created
        {
            int isCompiled;
            char infoLog[512];
            glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);

            if (!isCompiled)
            {
                glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
                std::cout << "Vertex shader compilation failed.\n" << infoLog << std::endl;
                return -1;
            }

            glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
            if (!isCompiled)
            {
                glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
                std::cout << "Fragment shader compilation failed.\n" << infoLog << std::endl;
                return -1;
            }
        }

        shaderProgram = glCreateProgram();

        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        //Check if they got successfully linked
        {
            int isLinked = 0;
            char infoLog[512];
            glGetProgramiv(shaderProgram, GL_LINK_STATUS, &isLinked);
            if (!isLinked)
            {
                glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
                std::cout << "Shader linking failed.\n" << infoLog << std::endl;
                return -1;
            }
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return 0;
    }

    void createVertexResources()
    {
        // Create Vertex Array
        glGenVertexArrays(1, &vertexArray);
        glBindVertexArray(vertexArray);

        // Create Vertex Buffer
        glGenBuffers(1, &vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

        // Create Element / Index Buffer
        glGenBuffers(1, &elementBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        // Unbind Buffers
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    int readFile(const std::string& filename, std::vector<char>& buffer)
    {
        std::ifstream file(filename, std::ios::binary | std::ios::ate);

        if (!file.is_open())
        {
            std::cout << "Failed to open file: " << filename << std::endl;
            return -1;
        }

        size_t fileSize = static_cast<size_t>(file.tellg());
        file.seekg(0);
        buffer.resize(fileSize);
        file.read(buffer.data(), fileSize);
        file.close();

        return 0;
    }

    void windowResizeCallback(GLFWwindow* window, int width, int height)
    {
        // Unused parameter
        (void)(window);

        glViewport(0, 0, width, height);
    }

    void RenderFrame()
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        glBindVertexArray(vertexArray);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
    }

    int Initialize()
    {
        int version = gladLoadGL(glfwGetProcAddress);

        if (GLAD_MAKE_VERSION(4, 6) != version)
        {
            std::cout << "Failed to initialize GLAD." << std::endl;
            return -1;
        }

        glViewport(0, 0, 1600, 900);

        glfwSetFramebufferSizeCallback(Backend::g_window, windowResizeCallback);

        createVertexResources();

        if (createShaders() == -1)
            return -1;

        return 0;
    }

    int Cleanup()
    {
         glDeleteProgram(shaderProgram);
         glDeleteBuffers(1, &vertexBuffer);
         glDeleteVertexArrays(1, &vertexArray);

        return 0;
    }
}
