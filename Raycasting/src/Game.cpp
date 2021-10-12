#include <iostream>
#include <chrono>
#include <fstream>

#include "../include/Game.h"
#include "../include/MazeGenerator.h"
#include "../include/Utilities.h"

const GameSettings Game::s_DefaultGameSettings = {
    {1, 1},  //Player Position
    {0, 0, 0},     //Sky Color
    {99, 97, 96},  //Floor Color
    {1920},        //Columns
    0.056f,          //Step Size
    pi_halves / 2,    //Player Angle
    pi_halves,     //FOV
    4.f,           //Zoom Scaling Factor
    50,            //Max View Distance
    2.f            //Player Speed
};

Game::Game() : m_WindowSize({ 1920, 1080}), m_Settings(s_DefaultGameSettings) {
    srand(time(nullptr));

    //Initializing OpenGL
    if (!glfwInit()) {
        std::cout << "Could not initialize glfw" << std::endl;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

    m_Window = glfwCreateWindow(m_WindowSize.width, m_WindowSize.height, "", nullptr, nullptr);

    glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    glfwMakeContextCurrent(m_Window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Could not load glad" << std::endl;
    }
    glViewport(0, 0, m_WindowSize.width, m_WindowSize.height);
    glClearColor(0.f, 0.f, 0.f, 1.0f);
    m_Shader.Initialize();
    m_Renderer.Initialize(m_Window);

    std::tie(m_Map, m_MapSize) = MapReader::Read("Maps/Map1.txt");
    m_PlayerPosition = m_Settings.PlayerPosition;
    m_PlayerAngle = m_Settings.PlayerAngle;
    m_PlayerSpeed = m_Settings.PlayerSpeed;
    m_FOV = m_Settings.FOV;
    m_ZoomedIn = false;
}

void Game::Start() {
    auto t1 = std::chrono::high_resolution_clock::now();
    double lastMouseX;
    float columnWidth = (float)m_WindowSize.width / (float)m_Settings.Columns;
    std::cout << columnWidth << std::endl;
    glfwGetCursorPos(m_Window, &lastMouseX, nullptr);

    while (!glfwWindowShouldClose(m_Window)) {
        float time = float(glfwGetTime());
        float sR = MapTo(sinf(time * 0.1), -1.f, 1.f, 0.f, 135.f);
        float sG = MapTo(sinf(time * 0.1), -1.f, 1.f, 0.f, 206.f);
        float sB = MapTo(sinf(time * 0.1), -1.f, 1.f, 0.f, 250.f);
        glClearColor(MAPC(sR), MAPC(sG), MAPC(sB), 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        //m_Renderer.DrawQuad({ 0, 0 }, { 1920, 1080 }, {(uint8_t)sR, (uint8_t)sG, (uint8_t)sB});
        m_DeltaTime = (static_cast<double>((std::chrono::high_resolution_clock::now() - t1).count())) / (1.0E9);
        t1 = std::chrono::high_resolution_clock::now();
        ProcessInput();

        Vector2<double> currMousePos;
        glfwGetCursorPos(m_Window, &currMousePos.x, &currMousePos.y);
        double deltaX = currMousePos.x - lastMouseX;
        m_PlayerAngle += deltaX * m_DeltaTime * 0.1;
        if (deltaX > 0 && currMousePos.x == 1919) {
            glfwSetCursorPos(m_Window, 0, currMousePos.y);
            currMousePos.x = 0;
        }
        else if (deltaX < 0 && currMousePos.x == 0) {
            glfwSetCursorPos(m_Window, 1920, currMousePos.y);
            currMousePos.x = 1920;
        }
        lastMouseX = currMousePos.x;

        for (int x = 0; x < m_WindowSize.width; x++) {
            float distToWall = 0.;
            float angle = (m_PlayerAngle - (m_FOV / 2.0f)) + ((float)x / (float)m_WindowSize.width) * m_FOV;
            bool hitWall = false;
            Vector2 rayDir = {m_Settings.StepSize * cosf(angle), m_Settings.StepSize * sinf(angle)};
            Vector2 rayPos(m_PlayerPosition);
            while (!hitWall && distToWall < m_Settings.MaxViewDist && rayPos.y >= 0 && rayPos.x >= 0) {
                rayPos += rayDir;
                distToWall += m_Settings.StepSize;
                if (rayPos.x >= m_MapSize.width || rayPos.y >= m_MapSize.height || rayPos.y < 0 || rayPos.x < 0) {
                    hitWall = true;
                    distToWall = m_Settings.MaxViewDist;
                }
                else {
                    if (InRange(int(rayPos.y), 0, int(m_Map.size())) && InRange(int(rayPos.x), 0, int(m_Map[0].size())) && m_Map[(int)rayPos.y][(int)rayPos.x] > 0) {
                        hitWall = true;
                    }
                }
            }
            double wallHeight = static_cast<double>(m_WindowSize.height) / distToWall;
            if (m_ZoomedIn) {
                wallHeight *= 4.f;
            }
            double wallY0 = (static_cast<double>(m_WindowSize.height) / 2) - (wallHeight / 2);
            Color currColor;
            if (int(rayPos.y) < m_Map.size() && int(rayPos.x) < m_Map[0].size()) {
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
                auto prevRayPos = rayPos - rayDir;
                bool onYSide = ((prevRayPos.x > (float(int(rayPos.x)) + 1.f)) && (m_Map[int(rayPos.y)][int(rayPos.x + 1)]) == 0) || ((prevRayPos.x < (float(int(rayPos.x)))) && (m_Map[int(rayPos.y)][int(rayPos.x - 1)]) == 0);
                if (onYSide) {
                    currColor = currColor / 2;
                }
                if (distToWall < m_Settings.MaxViewDist) {
                    m_Renderer.DrawQuad({ (float)(x * columnWidth), (float)wallY0 }, { columnWidth, (float)wallHeight }, currColor);
                }
            }
            m_Renderer.DrawQuad({ (float)(x * columnWidth), (float)(wallY0 + wallHeight) }, { columnWidth, (((float)(m_WindowSize.height - wallHeight)) / 2.f) }, m_Settings.FloorColor);
        }

        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }
}

void Game::CreateShaders(const char* vertexShaderPath, const char* fragmentShaderPath) {
    m_Shader.Create(vertexShaderPath, fragmentShaderPath);
    m_Shader.Use();
}

bool Game::KeyPressed(int key) {
    return glfwGetKey(m_Window, key) == GLFW_PRESS;
}

void Game::ProcessInput() {
    auto currPos = m_PlayerPosition;
    if (KeyPressed(GLFW_KEY_LEFT_SHIFT)) {
        m_PlayerSpeed = 4;
    }
    if (KeyPressed(GLFW_KEY_W)) {
        m_PlayerPosition.x += m_PlayerSpeed * cos(m_PlayerAngle) * m_DeltaTime;
        m_PlayerPosition.y += m_PlayerSpeed * sin(m_PlayerAngle) * m_DeltaTime;
    }
    if (KeyPressed(GLFW_KEY_S)) {
        m_PlayerPosition.x -= m_PlayerSpeed * cos(m_PlayerAngle) * m_DeltaTime;
        m_PlayerPosition.y -= m_PlayerSpeed * sin(m_PlayerAngle) * m_DeltaTime;
    }
    if (KeyPressed(GLFW_KEY_A)) {
        m_PlayerPosition.x += m_PlayerSpeed * sin(m_PlayerAngle) * m_DeltaTime;
        m_PlayerPosition.y -= m_PlayerSpeed * cos(m_PlayerAngle) * m_DeltaTime;
    }
    if (KeyPressed(GLFW_KEY_D)) {
        m_PlayerPosition.x -= m_PlayerSpeed * sin(m_PlayerAngle) * m_DeltaTime;
        m_PlayerPosition.y += m_PlayerSpeed * cos(m_PlayerAngle) * m_DeltaTime;
    }
    if (glfwGetMouseButton(m_Window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS) {
        m_ZoomedIn = true;
        m_FOV = pi / 8.;
        m_Shader.SetUniform("scoped", m_ZoomedIn);
    }
    else {
        m_ZoomedIn = false;
        m_FOV = m_Settings.FOV;
        m_Shader.SetUniform("scoped", m_ZoomedIn);
    }
    if (KeyPressed(GLFW_KEY_DOWN)) {
        m_FOV -= 0.1;
    }
    if (KeyPressed(GLFW_KEY_UP)) {
        m_FOV += 0.1;
    }
    if (KeyPressed(GLFW_KEY_Q)) {
        glfwSetWindowShouldClose(m_Window, GLFW_TRUE);
    }
    m_PlayerSpeed = 2;

    if (m_Map[(int)m_PlayerPosition.y][(int)m_PlayerPosition.x] != 0) {
        m_PlayerPosition = currPos;
    }
}