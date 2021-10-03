#include "../include/Game.h"

int main() {
    /*for (int i = 0; i < m.Dimensions().height; i++) {
        for (int j = 0; j < m.Dimensions().width; j++) {
            std::cout << m[i][j];
        }
        std::cout << std::endl;
    }*/
    Game game;
    game.CreateShaders("Shaders/shader.vert", "Shaders/shader.frag");
    game.Start();
}