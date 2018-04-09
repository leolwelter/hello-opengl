//
// Created by leo on 2/6/18.
//

#include "Game.h"

Game::Game(bool run)
{
    std::cout << "Initializing..." << std::endl;

    glfwInit(); // create window
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Dylan's Game", nullptr, nullptr);
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
    player = Creature(0.5f, -0.2f, 0.0f);
    enemy =  Creature(1.0f, -0.2f, 0.0f);
    creatures.push_back(player);
    creatures.push_back(enemy);

    // light sources
    glm::vec3 stdIntensities(0.1f, 0.4f, 1.0f);
    sun = LightSource(10.0f, 10.0f, 1.0f, glm::vec3(0.8f, 0.8f, 0.1f), stdIntensities, glm::vec3(0.6f, 0.6f, 0.6f), 'Z', 4.0f);
    moon = LightSource(-10.0f, -10.0f, -1.0f, glm::vec3(0.2f, 0.2f, 1.0f), stdIntensities, glm::vec3(0.2f, 0.2f, 0.2f), 'Z', 15.0f);
    LightSource uranium = LightSource(-1.0f, -10.0f, 10.0f, glm::vec3(0.3f, 0.7f, 0.1f), stdIntensities, glm::vec3(0.3f, 0.3f, 0.3f), 'X', 12.0f);
    LightSource ruby= LightSource(1.0f, 0.0f, -10.0f, glm::vec3(1.0f, .0f, 0.1f), stdIntensities, glm::vec3(1.0f, 1.0f, 1.0f), 'Y', 2.0f);

    lightSources.push_back(ruby);
    lightSources.push_back(uranium);
    lightSources.push_back(sun);
    lightSources.push_back(moon);

    // obstacles
    box = Obstacle(0.0f, 0.0f, 0.0f);
    floor = Obstacle(0.0f, -0.2f, 0.0f, 15.0f, 0.1f, 15.0f);
    Obstacle b1 = Obstacle(1.0f, 0.2f, 0.3f, 2.0f, 2.0f, 1.0f);
    Obstacle b2 = Obstacle(1.5f, 0.1f, 1.3f, 1.0f, 2.0f, 2.0f);
    Obstacle b3 = Obstacle(2.0f, 0.4f, 0.3f, 2.0f, 1.0f, 2.0f);
    Obstacle wallEast =  Obstacle(3.0f,  2.5f, 0.0f, 0.1f, 15.0f, 15.0f);
    Obstacle wallWest =  Obstacle(-3.0f, 2.5f, 0.0f, 0.1f, 15.0f, 15.0f);
    Obstacle wallSouth = Obstacle(0.0f,  2.5f, -3.0f, 15.0f, 15.0f, 0.1f);
    Obstacle wallNorth = Obstacle(0.0f,  2.5f, 3.0f, 15.0f, 15.0f, 0.1f);
    obstacles.push_back(b1);
    obstacles.push_back(b2);
    obstacles.push_back(b3);
    obstacles.push_back(box);
    obstacles.push_back(floor);
    obstacles.push_back(wallNorth);
    obstacles.push_back(wallSouth);
    obstacles.push_back(wallEast);
    obstacles.push_back(wallWest);

    for (auto &obj: creatures) {
        obj.shader = Shader("../src/_shaders/VertexShader.glsl", "../src/_shaders/FragmentShader.glsl");
    }
    for (auto &obj: lightSources) {
        obj.shader = Shader("../src/_shaders/VertexShader.glsl", "../src/_shaders/LightSourceFragmentShader.glsl");
    }
    for (auto &obj: obstacles) {
        obj.shader = Shader("../src/_shaders/VertexShader.glsl", "../src/_shaders/FragmentShader.glsl");
    }

    /* ---- texture loading ---- */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width, height, nChannels;
    unsigned char* texData = stbi_load("../assets/container.jpg", &width, &height, &nChannels, 0);
    glGenTextures(1, &boxTex);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, boxTex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(texData);

    texData = stbi_load("../assets/ship.png", &width, &height, &nChannels, 0);
    glGenTextures(1, &shipTex);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, shipTex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(texData);

    stbi_set_flip_vertically_on_load(true);
    texData = stbi_load("../assets/ship.png", &width, &height, &nChannels, 0);
    glGenTextures(1, &faceTex);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, faceTex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(texData);

    // assign textures to shader uniforms
    enemyShader.use();
    enemyShader.setInt("tex1", 1);

    playerShader.use();
    playerShader.setInt("tex1", 1);

    boxShader.use();
    boxShader.setInt("tex1", 0);
    boxShader.setInt("tex2", 2);

    /* ---- game logic initialization ---- */
    lastPlayerShotTime = glfwGetTime();
    lastEnemyShotTime = glfwGetTime();

    lastMouseX = SCR_WIDTH / 2;
    lastMouseY = SCR_HEIGHT / 2;
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    firstMouseInput = true;
}

void Game::run() {
    // bind textures
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, boxTex);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, shipTex);

    while(!glfwWindowShouldClose(window)) {
        glClearColor(.1f, .1f, .1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // calculate time delta
        float frameT = glfwGetTime();
        deltaT = frameT - lastFrameT;
        lastFrameT = frameT;

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

        for (auto &obj: lightSources) {
            obj.orbit(deltaT);
            renderObject(obj, view, projection);
        }

        for (auto &obj: obstacles) {
            renderObject(obj, view, projection);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // CLEAN UP
    glDeleteVertexArrays(1, &player.VAO);
    glDeleteVertexArrays(1, &enemy.VAO);
    glDeleteBuffers(1, &player.VBO);
    glDeleteBuffers(1, &enemy.VBO);
    glfwTerminate();
}


void Game::renderObject(GameObject object, glm::mat4 view, glm::mat4 projection) {
    object.shader.use();
    // view transformations
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, object.getPos());
    model = glm::scale(model, object.scale);
    object.shader.setMat4("model", model);
    object.shader.setMat4("view", view);
    object.shader.setMat4("projection", projection);
    object.shader.setVec3("material.ambient", object.material.ambient);
    object.shader.setVec3("material.diffuse", object.material.diffuse);
    object.shader.setVec3("material.specular", object.material.specular);
    object.shader.setFloat("material.shininess", object.material.shininess);

    for(int i = 0; i < lightSources.capacity(); i++) {
        glm::vec3 lPos = lightSources[i].getPos();
        object.shader.setVec3("pointLights[" + std::to_string(i) + "].position", lPos);
        object.shader.setVec3("pointLights[" + std::to_string(i) + "].ambient", lightSources[i].lIntensity.ambient);
        object.shader.setVec3("pointLights[" + std::to_string(i) + "].diffuse", lightSources[i].lIntensity.diffuse);
        object.shader.setVec3("pointLights[" + std::to_string(i) + "].specular", lightSources[i].lIntensity.specular);
    }

    glm::vec3 viewPos = camera.cameraPos;
    object.shader.setVec3("playerPos", viewPos);

    // draw
    glBindVertexArray(object.VAO);
    glDrawArrays(GL_TRIANGLES, 0, object.modelSize);
}


int Game::processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    // position
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.cameraPos += deltaT * player.getSpeed() * camera.cameraFront;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.cameraPos -= deltaT * player.getSpeed() * camera.cameraFront;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.cameraPos -= deltaT * player.getSpeed() * camera.cameraRight;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.cameraPos += deltaT * player.getSpeed() * camera.cameraRight;
    }

    return -1;
}

bool Game::playerCooldown() {
    double cooling = (glfwGetTime() - lastPlayerShotTime);
    return (cooling > 1);
}

bool Game::enemyCooldown() {
    double cooling = (glfwGetTime() - lastEnemyShotTime);
    return (cooling > 1);
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
}