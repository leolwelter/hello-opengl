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

const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 800;

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
    // constructors
    Game(void){}; // there can only be one

    // attributes
    Creature player;
    Creature enemy;
    Camera camera;

    Shader playerShader;
    Shader enemyShader;
    Shader boxShader;

    std::vector<Creature> creatures;
    std::vector<Obstacle> obstacles;
    std::vector<LightSource> pointLights;
    std::vector<LightSource> directionalLights;
    std::vector<LightSource> spotLights;

    unsigned int boxTex, shipTex, faceTex;
    float deltaT;
    float lastFrameT;
    float lastMouseX;
    float lastMouseY;
    bool firstMouseInput;

    // methods
    void renderObject(GameObject object, glm::mat4 view, glm::mat4 projection);    int processInput(GLFWwindow *window);
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};


#endif //TEXTGAME_GAME_H
