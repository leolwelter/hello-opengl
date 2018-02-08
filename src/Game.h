//
// Created by leo on 2/6/18.
//

#ifndef TEXTGAME_GAME_H
#define TEXTGAME_GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Creature.h"
#include <iostream>

const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 600;

class Game {
public:
    Game();
    void run();
private:
    Creature player;
    Creature enemy;

    GLFWwindow* window;
    unsigned int playerShader;
    unsigned int enemyShader;

    void getModelVertices(Creature creature);
    int processInput(GLFWwindow *window);
    void generateVertexObjects(Creature creature);
    void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};


#endif //TEXTGAME_GAME_H
