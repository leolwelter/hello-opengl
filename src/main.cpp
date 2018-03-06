#include "Game.h"

int main(int argc, char** argv) {
    // initialize
    Game &game = Game::getInstance();
    // register static callbacks
    glfwSetCursorPosCallback(game.window, &Game::mouse_callback_static);

    // begin game logic
    game.run();
    return 0;
}

