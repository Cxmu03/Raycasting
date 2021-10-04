#include "../include/Game.h"

int main() {
    Game game;
    game.CreateShaders("Shaders/shader.vert", "Shaders/shader.frag");
    game.Start();
}