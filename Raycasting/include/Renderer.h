#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../include/Vector2.h"
#include "../include/Color.h"
#include "../include/Size.h"

class Renderer {
public:
    Renderer() : Renderer(nullptr) {}
    Renderer(GLFWwindow* window);
public:
    void DrawQuad(Vector2<float> position, Size<float> size, Color fillColor);
    void Initialize();
    void Initialize(GLFWwindow* window);
private:
    GLFWwindow* m_Window;
    unsigned m_VAO, m_VBO, m_EBO;

    static const unsigned s_QuadIndices[];
};