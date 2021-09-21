#include <iostream>
#include <chrono>

#include "../include/Game.h"

const GameSettings Game::s_DefaultGameSettings = {
    {0.f, 0.f},    //PlayerPosition
    {0, 0, 0},     //Sky Color
    {99, 97, 96},  //Floor Color
    {1920},        //Columns
    0.1f,          //Step Size
    -pi_halves,    //Player Angle
    pi_halves,     //FOV
    15             //Max View Distance
};

Game::Game() : m_WindowSize({ 1920, 1080 }), m_Settings(s_DefaultGameSettings) {
    if (!glfwInit()) {
        std::cout << "Could not initialize glfw" << std::endl;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

    m_Window = glfwCreateWindow(m_WindowSize.width, m_WindowSize.height, "", nullptr, nullptr);

    glfwMakeContextCurrent(m_Window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Could not load glad" << std::endl;
    }
    glViewport(0, 0, m_WindowSize.width, m_WindowSize.height);
    glClearColor(0.f, 0.f, 0.f, 1.0f);
    m_Shader.Initialize();
    m_Renderer.Initialize(m_Window);
}

void Game::Start() {
    auto t1 = std::chrono::high_resolution_clock::now();
    while (!glfwWindowShouldClose(m_Window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        auto deltaTime = (static_cast<double>((std::chrono::high_resolution_clock::now() - t1).count())) / (1.0E9);
        t1 = std::chrono::high_resolution_clock::now();
        //std::cout << fps << std::endl;
        if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS) {
            m_PlayerPosition.x += 2.f * cosf(m_PlayerAngle) * (float)deltaTime;
            m_PlayerPosition.y += 2.f * sinf(m_PlayerAngle) * (float)deltaTime;
        }
        if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS) {
            m_PlayerPosition.x -= 2.f * cosf(m_PlayerAngle) * (float)deltaTime;
            m_PlayerPosition.y -= 2.f * sinf(m_PlayerAngle) * (float)deltaTime;
        }
        if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS) {
            m_PlayerAngle -= 2 * deltaTime;
        }
        if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS) {
           m_PlayerAngle += 2 * deltaTime;
        }

        for (int x = 0; x < m_WindowSize.width; x++) {
            double distToWall = 0.;
            double angle = (m_PlayerAngle - (pi / 2.f) / 2.0f) + ((double)x / (double)m_WindowSize.width) * (pi / 2);
            bool hitWall = false;
            Vector2 rayDir = { m_Settings.StepSize * cosf(angle), m_Settings.StepSize * sinf(angle) };
            Vector2 rayPos(m_PlayerPosition);
            while (!hitWall && distToWall < m_Settings.MaxViewDist && rayPos.x >= 0 && rayPos.y >= 0) {
                rayPos += rayDir;
                distToWall += m_Settings.StepSize;
                if (rayPos.x >= m_MapSize.width || rayPos.y >= m_MapSize.width || rayPos.y < 0 || rayPos.x < 0) {
                    hitWall = true;
                    distToWall = m_Settings.MaxViewDist;
                }
                else {
                    if (m_Map[(int)rayPos.y][(int)rayPos.x] > 0) {
                        hitWall = true;
                    }
                }
            }
            double wallHeight = static_cast<double>(m_WindowSize.height) / distToWall;
            double wallY0 = (static_cast<double>(m_WindowSize.height) / 2) - (wallHeight / 2);
            Color currColor;
            switch (m_Map[(int)rayPos.y][(int)rayPos.x]) {
                case 1:
                    currColor = Color::Red;
                    break;
                case 2:
                    currColor = Color::Green;
                    break;
                case 3:
                    currColor = Color::Blue;
                    break;
                case 4:
                    currColor = Color::White;
                    break;
                default:
                    currColor = Color::Yellow;
                    break;

            }
            if (distToWall < m_Settings.MaxViewDist) {
                m_Renderer.DrawRectangle({ (float)x, (float)wallY0 }, { 1, (float)wallHeight }, currColor);
            }
            //Boden (99, 97, 96)
            m_Renderer.DrawRectangle({ (float)x, (float)(wallY0 + wallHeight) }, { 1, (((float)(m_WindowSize.height - wallHeight)) / 2.f) }, m_Settings.FloorColor);
        }

        //glClear(GL_COLOR_BUFFER_BIT);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }
}

void Game::CreateShaders(const char* vertexShaderPath, const char* fragmentShaderPath) {
    m_Shader.Create(vertexShaderPath, fragmentShaderPath);
    m_Shader.Use();
}