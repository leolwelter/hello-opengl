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

const unsigned int MAX_SCR_WIDTH = 1366;
const unsigned int MAX_SCR_HEIGHT = 768;
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 720;
const double FLASHLIGHT_COOLDOWN = 0.4;
const double BULLET_COOLDOWN = 0.4;

static char *nanosuitModel = "/home/leo/work/textgame/assets/nanosuit_model/nanosuit.obj";
static char *dragonModel = "/home/leo/work/textgame/assets/black_dragon_model/Dragon 2.5_fbx.fbx";
static char *farmHouseModel = "/home/leo/work/textgame/assets/farmhouse_model/farmhouse_obj.obj";
static char *eyeModel = "/home/leo/work/textgame/assets/eyeball_model/eyeball.obj";
static char *boxModel = "/home/leo/work/textgame/assets/box_model/box.obj";

//struct Hand {
//    Hand() {
//        palm   = Creature(glm::vec3( 0.0f,  0.0f,  0.0f), glm::vec3(1.0f, 1.0f, 0.1f), boxModel);
//        thumb  = Creature(glm::vec3(-1.0f, -1.0f,  0.0f), glm::vec3(1.0f, 0.1f, 0.1f), boxModel);
//        index  = Creature(glm::vec3(-1.0f,  0.5f,  0.0f), glm::vec3(0.1f, 1.0f, 0.1f), boxModel);
//        middle = Creature(glm::vec3( 0.5f,  0.5f,  0.0f), glm::vec3(0.1f, 1.0f, 0.1f), boxModel);
//        ring   = Creature(glm::vec3( 1.0f,  0.5f,  0.0f), glm::vec3(0.1f, 1.0f, 0.1f), boxModel);
//        pinky  = Creature(glm::vec3( 1.5f,  0.5f,  0.0f), glm::vec3(0.1f, 1.0f, 0.1f), boxModel);
//        handParts.push_back(palm   );
//        handParts.push_back(thumb  );
//        handParts.push_back(index  );
//        handParts.push_back(middle );
//        handParts.push_back(ring   );
//        handParts.push_back(pinky  );
//    }
//    Creature palm;
//    Creature thumb;
//    Creature index;
//    Creature middle;
//    Creature ring;
//    Creature pinky;
//    std::vector<Creature> handParts;
//};

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
    Game(){}; // there can only be one

    // attributes
    Camera camera;
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

    void moveCameraView(double dX, double dY);
};


#endif //TEXTGAME_GAME_H
