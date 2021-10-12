#include "../include/Game.h"

int main() {
    Game game;
    game.CreateShaders("shaders/shader.vert", "shaders/shader.frag");
    game.Start();
}