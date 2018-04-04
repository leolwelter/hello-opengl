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
#include "LightSource.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

class Game {
public:
    Game(bool run);
    void run();
    static Game& getInstance()
    {
        static Game instance(true);
        return instance;
    }

    // need a static wrapper for glfw callback
    static void mouse_callback_static(GLFWwindow* window, double x, double y)
    {
        // uses a Game singleton's "mouse_callback_static" to call the
        // actual implementation
        getInstance().mouse_callback(window, x, y);
    }

    // actual implementation of callbacks
    void mouse_callback(GLFWwindow* window, double x, double y);

    GLFWwindow* window;

private:
    Game(void){}; // there can only be one

    Creature player;
    Creature enemy;
    Obstacle box;
    Obstacle floor;
    Camera camera;
    LightSource sun;

    Shader playerShader;
    Shader enemyShader;
    Shader bulletShader;
    Shader boxShader;
    Shader sunShader;

    std::vector<Bullet> bullets;
    std::vector<GameObject> objects;

    unsigned int boxTex, shipTex, faceTex;
    double lastPlayerShotTime;
    double lastEnemyShotTime;
    float deltaT;
    float lastFrameT;
    float lastMouseX;
    float lastMouseY;

    void renderObject(GameObject object, Shader shader, glm::mat4 model, glm::mat4 view, glm::mat4 projection);    int processInput(GLFWwindow *window);
    void generateVertexObjects(GameObject* object);
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void spawnBullet(int side);
    bool playerCooldown();
    bool enemyCooldown();

    bool firstMouseInput;
};


#endif //TEXTGAME_GAME_H
