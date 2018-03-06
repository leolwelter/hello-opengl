//
// Created by leo on 2/6/18.
//

#ifndef TEXTGAME_GAME_H
#define TEXTGAME_GAME_H


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>

#include "stb_image.h"
#include "Creature.h"
#include "Bullet.h"
#include "Shader.h"
#include "Obstacle.h"
#include "Camera.h"

const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 600;

class Game {
public:
    Game();
    void run();
private:
    Creature player;
    Creature enemy;
    Obstacle box;
    Camera camera;

    GLFWwindow* window;
    Shader playerShader;
    Shader enemyShader;
    Shader bulletShader;
    Shader boxShader;

    unsigned int boxTex, shipTex, faceTex;

    void getModelVertices(GameObject* object);
    int processInput(GLFWwindow *window);
    void generateVertexObjects(GameObject* object);
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

    void spawnBullet(int side);
    std::vector<Bullet> bullets;

    bool playerCooldown();
    bool enemyCooldown();
    double lastPlayerShotTime;
    double lastEnemyShotTime;
};


#endif //TEXTGAME_GAME_H
