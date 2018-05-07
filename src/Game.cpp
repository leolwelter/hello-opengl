//
// Created by leo on 2/6/18.
//

#include "Game.h"

Game::Game(bool debug)
{
    std::cout << "Initializing..." << std::endl;

    glfwInit(); // create window
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Dylan's Game", nullptr, nullptr);
//    glfwSetWindowPos(window, MAX_SCR_WIDTH / 4, MAX_SCR_HEIGHT);
    glfwMakeContextCurrent(window);

    // init window
    if (window == NULL) {
        std::cout << "GL Borked :(" << std::endl;
        glfwTerminate();
        return;
    }

    // init GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "GLAD Borked :(" << std::endl;
        return;
    }

    // now we can work with gl functions
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glEnable(GL_DEPTH_TEST);

    /* ---- game objects ----*/
    // creatures
    char *nanosuitModel = "/home/leo/work/textgame/assets/nanosuit_model/nanosuit.obj";
    char *dragonModel = "/home/leo/work/textgame/assets/black_dragon_model/Dragon 2.5_fbx.fbx";
    char *farmHouseModel = "/home/leo/work/textgame/assets/farmhouse_model/farmhouse_obj.obj";
    char *eyeModel = "/home/leo/work/textgame/assets/eyeball_model/eyeball.obj";
    char *boxModel = "/home/leo/work/textgame/assets/box_model/box.obj";

    float creatureYaw = 0.0f;
    int numCreatures = 6;
    float circRadius = 3.0f;
    float tmpX = circRadius;
    float tmpZ = circRadius;
    float dTheta = 360.0f / numCreatures;
    for (int i = 0; i < numCreatures; i++) {
        Creature cr(glm::vec3(tmpX, 0.0f, tmpZ), glm::vec3(.2f), nanosuitModel);
        creatureYaw += dTheta;
        cr.yaw = creatureYaw;
        cr.pitch = -90.0f;
        tmpX = cr.position.x * cos((M_PI * dTheta) / 180) - cr.position.z * sin((M_PI * dTheta) / 180);
        tmpZ = cr.position.z * cos((M_PI * dTheta) / 180) + cr.position.x * sin((M_PI * dTheta) / 180);
        creatures.push_back(cr);
    }


    // light sources
//    LightSource sun(glm::vec3(2.0f, 10.0f, 2.0f), glm::vec3(0.05f), boxModel, LIGHTSOURCE_HIGH_INTENSITY, glm::vec3(.9f, .8f, .7f), 'N');
//    sun.lDirection = glm::vec3(-2.0f, -1.0f, -2.0f);
//    directionalLights.push_back(sun);

    srand((unsigned int)glfwGetTime());
    int bound = 10;
    char orbits [] = {'X', 'Y', 'Z'};

    for (int i = 0; i < 5; i++) {
        glm::vec3 randPos(rand() % bound, rand() % (bound / 2), rand() % bound);
        glm::vec3 randColor((rand() % 100) / 100.0f, (rand() % 100) / 100.0f, (rand() % 100) / 100.0f);
        LightSource light(randPos, glm::vec3(0.1f), boxModel, LIGHTSOURCE_HIGH_INTENSITY, randColor, orbits[rand() % 3]);
        pointLights.push_back(light);
    }


    LightSource flashLight(camera.cameraPos, glm::vec3(0.05f), boxModel, LIGHTSOURCE_STD_INTENSITY, glm::vec3(.7f, .7f, .9f), 'N');
    flashLight.lDirection = camera.cameraTarget;
    spotLights.push_back(flashLight);

    // obstacles

    // compile and assign shaders for every GameObject
    for (auto &obj: creatures) {
        obj.shader = Shader("../src/_shaders/VertexShader.glsl", "../src/_shaders/FragmentShader.glsl");
    }
    for (auto &obj: obstacles) {
        obj.shader = Shader("../src/_shaders/VertexShader.glsl", "../src/_shaders/FragmentShader.glsl");
    }
    for (auto &obj: pointLights) {
        if (obj.rotAxis != 'N')
            obj.orbit(deltaT);
        obj.shader = Shader("../src/_shaders/VertexShader.glsl", "../src/_shaders/FragmentShader.glsl");
    }
    for (auto &obj: directionalLights) {
        obj.shader = Shader("../src/_shaders/VertexShader.glsl", "../src/_shaders/FragmentShader.glsl");
    }
    for (auto &obj: spotLights) {
        obj.shader = Shader("../src/_shaders/VertexShader.glsl", "../src/_shaders/FragmentShader.glsl");
    }

    /* ---- game logic initialization ---- */
    lastMouseX = SCR_WIDTH / 2;
    lastMouseY = SCR_HEIGHT / 2;
    firstMouseInput = true;
    flashlightCooldown = 0.0f;
    playerBulletCooldown = 0.0f;

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Game::run() {
    while(!glfwWindowShouldClose(window)) {
        glClearColor(.1f, .1f, .1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // calculate time delta
        float frameT = glfwGetTime();
        deltaT = frameT - lastFrameT;
        lastFrameT = frameT;

        // update cooldowns
        flashlightCooldown = (flashlightCooldown <= 0) ? 0 : flashlightCooldown - deltaT;

        // user input and calculations
        processInput(window);

        // view matrix, used for world coordinate space (glm::lookAt)
        glm::mat4 view = camera.getView();

        // projection matrix (perspective not ortho)
        glm::mat4 projection(1.0f);
        projection = glm::perspective(glm::radians(60.0f), (float)SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.0f);


        for (auto &obj: creatures) {
            renderObject(obj, view, projection);
        }

        for (auto &obj: obstacles) {
            renderObject(obj, view, projection);
        }

        for (auto &obj: pointLights) {
            obj.orbit(deltaT);
            renderObject(obj, view, projection);
        }
//
//        for (auto &obj: directionalLights) {
//            renderObject(obj, view, projection);
//        }
//
//        for (auto &obj: spotLights) {
//            renderObject(obj, view, projection);
//        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // CLEAN UP
    glfwTerminate();
}


void Game::renderObject(GameObject object, glm::mat4 view, glm::mat4 projection) {
    object.shader.use();

    // model transformation
    float faceX = cos(glm::radians(object.pitch)) * cos(glm::radians(object.yaw));
    float faceY = sin(glm::radians(object.pitch));
    float faceZ = cos(glm::radians(object.pitch)) * sin(glm::radians(object.yaw));
    object.modelFront = glm::normalize(glm::vec3(faceX, faceY, faceZ));
    object.modelRight = glm::normalize(glm::cross(object.modelFront, object.modelUp));

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, object.position);
    model = glm::scale(model, object.scale);
    model = glm::rotate(model, glm::degrees(object.yaw), object.modelUp);
    model = glm::rotate(model, glm::degrees(object.pitch), object.modelRight);
    object.shader.setMat4("model", model);
    object.shader.setMat4("view", view);
    object.shader.setMat4("projection", projection);

    // view transformations
    glm::vec3 viewPos = camera.cameraPos;
    object.shader.setVec3("playerPos", viewPos);

    // set shader materials
    object.shader.setVec3("material.ambient", object.material.ambient);
    object.shader.setVec3("material.diffuse", object.material.diffuse);
    object.shader.setVec3("material.specular", object.material.specular);
    object.shader.setFloat("material.shininess", object.material.shininess);

    // set shader lighting properties
    for(int i = 0; i < pointLights.capacity(); i++) {
        glm::vec3 lPos = pointLights[i].position;
        object.shader.setVec3("pointLights[" + std::to_string(i) + "].position", lPos);
        object.shader.setVec3("pointLights[" + std::to_string(i) + "].ambient", pointLights[i].lIntensity.ambient);
        object.shader.setVec3("pointLights[" + std::to_string(i) + "].diffuse", pointLights[i].lIntensity.diffuse);
        object.shader.setVec3("pointLights[" + std::to_string(i) + "].specular", pointLights[i].lIntensity.specular);
        object.shader.setFloat("pointLights[" + std::to_string(i) + "].constant", pointLights[i].attenConstant);
        object.shader.setFloat("pointLights[" + std::to_string(i) + "].linear", pointLights[i].attenLinear);
        object.shader.setFloat("pointLights[" + std::to_string(i) + "].quadratic", pointLights[i].attenQuad);
    }

    for(int i = 0; i < directionalLights.capacity(); i++) {
        object.shader.setVec3("dirLights[" + std::to_string(i) + "].direction", directionalLights[i].lDirection);
        object.shader.setVec3("dirLights[" + std::to_string(i) + "].diffuse", directionalLights[i].lIntensity.diffuse);
        object.shader.setVec3("dirLights[" + std::to_string(i) + "].specular", directionalLights[i].lIntensity.specular);
    }

    for(int i = 0; i < spotLights.capacity(); i++) {
        object.shader.setVec3("spotLights[" + std::to_string(i) + "].position", spotLights[i].position);
        object.shader.setVec3("spotLights[" + std::to_string(i) + "].spotDir", spotLights[i].lDirection);
        object.shader.setFloat("spotLights[" + std::to_string(i) + "].cutoffAngle", glm::cos(glm::radians(spotLights[i].cutoffAngle)));
        object.shader.setFloat("spotLights[" + std::to_string(i) + "].cutoffOuter", glm::cos(glm::radians(spotLights[i].cutoffOuter)));
        object.shader.setVec3("spotLights[" + std::to_string(i) + "].diffuse", spotLights[i].lIntensity.diffuse);
        object.shader.setVec3("spotLights[" + std::to_string(i) + "].specular", spotLights[i].lIntensity.specular);
        object.shader.setFloat("spotLights[" + std::to_string(i) + "].constant", spotLights[i].attenConstant);
        object.shader.setFloat("spotLights[" + std::to_string(i) + "].linear", spotLights[i].attenLinear);
        object.shader.setFloat("spotLights[" + std::to_string(i) + "].quadratic", spotLights[i].attenQuad);
    }

    // draw
    object.model.draw(object.shader);
}


int Game::processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    // position
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.cameraPos += deltaT * CAMERA_SPEED * camera.cameraFront;
        spotLights[0].position = camera.cameraPos;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.cameraPos -= deltaT * CAMERA_SPEED * camera.cameraFront;
        spotLights[0].position = camera.cameraPos;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.cameraPos -= deltaT * CAMERA_SPEED * camera.cameraRight;
        spotLights[0].position = camera.cameraPos;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.cameraPos += deltaT * CAMERA_SPEED * camera.cameraRight;
        spotLights[0].position = camera.cameraPos;
    }
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
        if (flashlightCooldown <= 0) {
            flashlightCooldown = FLASHLIGHT_COOLDOWN;
            if (spotLights.at(0).lIntensity.diffuse == glm::vec3(0.0f)) {
                spotLights.at(0).lIntensity = {spotLights.at(0).color, spotLights.at(0).color, spotLights.at(0).color};
            }
            else {
                spotLights.at(0).lIntensity.diffuse = glm::vec3(0.0f);
                spotLights.at(0).lIntensity.ambient= glm::vec3(0.0f);
                spotLights.at(0).lIntensity.specular = glm::vec3(0.0f);
            }
        }
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        for (auto &obj: creatures) {
            obj.pitch -= deltaT * 0.01f;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        for (auto &obj: creatures) {
            obj.pitch += deltaT * 0.01f;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        for (auto &obj: creatures) {
            obj.yaw -= deltaT * 0.01f;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        for (auto &obj: creatures) {
            obj.yaw += deltaT * 0.01f;
        }
    }

    return -1;
}


void Game::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Game::mouse_callback(GLFWwindow* window, double x, double y) {
    // account for large difference of mouse position when cursor enters
    if (firstMouseInput) {
        lastMouseX = x;
        lastMouseY = y;
        firstMouseInput = false;
    }

    // calculate mouse offset change
    float dX = x - lastMouseX;
    float dY = lastMouseY - y;
    lastMouseX = x;
    lastMouseY = y;

    dX *= camera.sensitivity;
    dY *= camera.sensitivity;


    // add offset value to camera yaw/pitch
    camera.pitch += dY;
    camera.yaw += dX;

    if (camera.pitch > 89.0f)
        camera.pitch = 89.0f;
    else if (camera.pitch < -89.0f)
        camera.pitch = -89.0f;

    // recalculate camera front vector
    float faceX = cos(glm::radians(camera.pitch)) * cos(glm::radians(camera.yaw));
    float faceY = sin(glm::radians(camera.pitch));
    float faceZ = cos(glm::radians(camera.pitch)) * sin(glm::radians(camera.yaw));
    camera.cameraFront = glm::normalize(glm::vec3(faceX, faceY, faceZ));
    camera.cameraRight = glm::normalize(glm::cross(camera.cameraFront, camera.cameraUp));
    camera.cameraTarget = glm::normalize(-camera.cameraFront);

    // set flashlight direction to camera's target
    spotLights.at(0).lDirection = camera.cameraFront; //camera.cameraTarget;
}
