#include "../include/Renderer.h"
#include "../include/Utilities.h"

const unsigned Renderer::s_QuadIndices[] = {
    0, 1, 2,
    2, 3, 0
};

Renderer::Renderer(GLFWwindow* window) : m_Window(window) { }

void Renderer::Initialize(GLFWwindow* window) {
    m_Window = window;
    Initialize();
}

void Renderer::Initialize() {
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);
}

void Renderer::DrawQuad(Vector2<float> position, Size<float> size, Color fillColor) {
    int windowWidth, windowHeight;
    glfwGetWindowSize(m_Window, &windowWidth, &windowHeight);

    float r = MapTo(static_cast<float>(fillColor.r), 0.f, 255.f, 0.f, 1.f);
    float g = MapTo(static_cast<float>(fillColor.g), 0.f, 255.f, 0.f, 1.f);
    float b = MapTo(static_cast<float>(fillColor.b), 0.f, 255.f, 0.f, 1.f);

    float x0 = MapTo(position.x, 0.f, (float)windowWidth, -1.f, 1.f);
    float y0 = MapTo(position.y, 0.f, (float)windowHeight, 1.f, -1.f);

    float x1 = MapTo(position.x + size.width, 0.f, (float)windowWidth , -1.f, 1.f);
    float y1 = MapTo(position.y + size.height, 0.f, (float)windowHeight, 1.f, -1.f);

    float vertices[] = {
        //Positions    Colors
        x0, y1, 0.f,   r, g, b,   //Bottom left
        x0, y0, 0.f,   r, g, b,   //Top Left
        x1, y0, 0.f,   r, g, b,   //Top Right
        x1, y1, 0.f,   r, g, b    //Bottom Right
    };

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(s_QuadIndices), s_QuadIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, 6 * sizeof(GL_FLOAT), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, 6 * sizeof(GL_FLOAT), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
