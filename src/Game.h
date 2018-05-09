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
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <leap/Leap.h>

#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>

#include "stb_image.h"
#include "Creature.h"
#include "Shader.h"
#include "Obstacle.h"
#include "Camera.h"
#include "LightSource.h"
#include "ControlInterface.h"

const unsigned int MAX_SCR_WIDTH = 1366;
const unsigned int MAX_SCR_HEIGHT = 768;
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 720;
const double FLASHLIGHT_COOLDOWN = 0.4;
const double BULLET_COOLDOWN = 0.4;

class Game {
public:
    // constructors
    Game(bool debug);
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

    // methods
    // actual implementation of callbacks
    void mouse_callback(GLFWwindow* window, double x, double y);
    void run();

    // attributes
    GLFWwindow* window;

private:
    // constructors
    Game(void){}; // there can only be one

    // attributes
    Camera camera;
    ControlLeap controlListener;
    Leap::Controller leapController;

    std::vector<Creature> creatures;
    std::vector<Obstacle> obstacles;
    std::vector<LightSource> pointLights;
    std::vector<LightSource> directionalLights;
    std::vector<LightSource> spotLights;

    float deltaT;
    float lastFrameT;
    float lastMouseX;
    float lastMouseY;
    bool firstMouseInput;
    float flashlightCooldown;
    float playerBulletCooldown;

    // methods
    void renderObject(GameObject object, glm::mat4 view, glm::mat4 projection);
    int processInput(GLFWwindow *window);
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};


#endif //TEXTGAME_GAME_H
