//
// Created by leo on 2/6/18.
//

#ifndef TEXTGAME_GAME_H
#define TEXTGAME_GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Creature.h"
#include "Bullet.h"
#include <iostream>
#include <vector>

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
    unsigned int bulletShader;

    void getModelVertices(GameObject* object);
    int processInput(GLFWwindow *window);
    void generateVertexObjects(GameObject* object);
    void framebuffer_size_callback(GLFWwindow* window, int width, int height);

    // list of bullets
    std::vector<Bullet> bullets;
};


#endif //TEXTGAME_GAME_H
