#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../include/Vector2.h"
#include "../include/Size.h"
#include "../include/Shader.h"
#include "../include/Renderer.h"
#include "../include/Map.h"

//TODO implement maybe later
struct WindowSettings {

};

struct GameSettings {
    Vector2<float> PlayerPosition;
    Color SkyColor;
    Color FloorColor;
    uint16_t Columns;
    float StepSize;
    float PlayerAngle;
    float FOV;
    float ZoomScalingFactor;
    float MaxViewDist;
    float PlayerSpeed;
};

class Game {
public:
    Game();

public:
    void Start();
    void CreateShaders(const char* vertexShaderPath, const char* fragmentShaderPath);

private:
    void ProcessInput();
    bool KeyPressed(int key);

private:
    GLFWwindow* m_Window;
    Size<uint16_t> m_WindowSize;
    Shader m_Shader;
    Renderer m_Renderer;

    GameSettings m_Settings;

    /*Map m_Map;*/
    std::vector<std::vector<uint8_t>> m_Map;
    Size<size_t> m_MapSize;
    Vector2<float> m_PlayerPosition;
    bool m_ZoomedIn;
    float m_PlayerAngle;
    float m_PlayerSpeed;
    float m_FOV;
    float m_DeltaTime;

    static const GameSettings s_DefaultGameSettings;
};