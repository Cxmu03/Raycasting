#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <filesystem>
#include <chrono>

#include "../include/Shader.h"
#include "../include/Utilities.h"
#include "../include/Vector2.h"
#include "../include/Color.h"
#include "../include/Renderer.h"
#include "../include/Game.h"
#include "../include/MazeGenerator.h"

constexpr auto mapWidth = 25;
constexpr auto mapHeight = 25;
constexpr double frameTime = 1. / 60.;
constexpr double maxViewDist = 50;

const Color floorColor = { 99, 97, 96 };

int width = 1920;
int height = 1080;

float rectX = 250.f;
float rectY = 100.f;
float theta = pi;
float delta_time = 0.f;
std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

void framebuffer_size_callback(GLFWwindow*, int, int); 
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

void rotate(float, float&, float&, float, float); 

//int worldMap[mapHeight][mapWidth] =
//{
//    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
//    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
//    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
//    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,1,3,0,3,0,0,0,1},
//    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
//    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
//    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,1,3,0,3,0,0,0,1},
//    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
//};

int main() {
    /*Game game;
    game.CreateShaders("Shaders/shader.vert", "Shaders/shader.frag");
    game.Start();*/
    auto worldMap = MazeGenerator::Automata<30, 30>();
    for (const auto& row : worldMap) {
        for (auto cell : row) {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }
    if (!glfwInit()) {
        std::cout << "Could not load GLFW" << std::endl;
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

    GLFWwindow* window = glfwCreateWindow(width, height, "Test", nullptr, nullptr);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "ERROR >> Could not load glad" << std::endl;
        return -1;
    }

    glViewport(0, 0, width, height);

    //Game game;

    Shader shader("Shaders/shader.vert", "Shaders/shader.frag");
    shader.Use();
    
    Renderer renderer(window);
    renderer.Initialize();

    Vector2<double> playerPos = {20., 20.};
    double playerAngle = 0;
    double stepSize = 0.1;

    double lastMouseX;
    glfwGetCursorPos(window, &lastMouseX, nullptr);

    glClearColor(0.f, 0.f, 0.f, 1.0f);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        auto deltaTime = (static_cast<double>((std::chrono::high_resolution_clock::now() - t1).count())) / (1.0E9);
        t1 = std::chrono::high_resolution_clock::now();
        //std::cout << fps << std::endl;
        auto currPos = playerPos;
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            playerPos.x += 2 * cos(playerAngle) * deltaTime;
            playerPos.y += 2 * sin(playerAngle) * deltaTime;
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            playerPos.x -= 2 * cos(playerAngle) * deltaTime;
            playerPos.y -= 2 * sin(playerAngle) * deltaTime;
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            playerPos.x += 2 * sin(playerAngle) * deltaTime;
            playerPos.y -= 2 * cos(playerAngle) * deltaTime;
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            playerPos.x -= 2 * sin(playerAngle) * deltaTime;
            playerPos.y += 2 * cos(playerAngle) * deltaTime;
        }

        if (worldMap[(int)playerPos.y][(int)playerPos.x] != 0) {
            playerPos = currPos;
        }
        Vector2<double> currMousePos;
        glfwGetCursorPos(window, &currMousePos.x, &currMousePos.y);
        double deltaX = currMousePos.x - lastMouseX;
        playerAngle += deltaX * deltaTime * 0.1;
        if (deltaX > 0 && currMousePos.x > 1800) {
            glfwSetCursorPos(window, 200, currMousePos.y);
            currMousePos.x = 200;
        }
        else if (deltaX < 0 && currMousePos.x < 120) {
            glfwSetCursorPos(window, 1720, currMousePos.y);
            currMousePos.x = 1720;
        }
        lastMouseX = currMousePos.x;


        for (int x = 0; x < width; x++) {
            double distToWall = 0.;
            double angle = (playerAngle - (pi / 2) / 2.0f) + ((double)x / (double)width) * (pi / 2);
            bool hitWall = false;
            Vector2 rayDir = {stepSize * cos(angle), stepSize * sin(angle)};
            Vector2 rayPos(playerPos);
            while (!hitWall && distToWall < maxViewDist) {
                rayPos += rayDir;
                distToWall += stepSize;
                if (rayPos.x >= mapWidth || rayPos.y >= mapHeight || rayPos.y < 0 || rayPos.x < 0) {
                    hitWall = true;
                    distToWall = maxViewDist;
                }
                else {
                    if (worldMap[(int)rayPos.y][(int)rayPos.x] > 0) {
                        hitWall = true;
                    }
                }
            }
            double wallHeight = static_cast<double>(height) / distToWall;
            double wallY0 = (static_cast<double>(height) / 2) - (wallHeight / 2);
            Color currColor;
            switch (worldMap[(int)rayPos.y][(int)rayPos.x]) {
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
            if (distToWall < maxViewDist) {
                renderer.DrawRectangle({ (float)x, (float)wallY0 }, { 1, (float)wallHeight }, currColor);
            }
            //Boden (99, 97, 96)
            renderer.DrawRectangle({ (float)x, (float)(wallY0 + wallHeight) }, { 1, (((float)(height - wallHeight)) / 2.f) }, floorColor);
        }

        //glClear(GL_COLOR_BUFFER_BIT);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}