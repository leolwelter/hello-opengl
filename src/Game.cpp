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

    /* ---- SHADER SOURCE AND COMPILATION ---- */
    playerShader = Shader("../src/_shaders/VertexShader.glsl", "../src/_shaders/ShipShader.glsl");
    enemyShader = Shader("../src/_shaders/VertexShader.glsl", "../src/_shaders/ShipShader.glsl");
    bulletShader = Shader("../src/_shaders/VertexShader.glsl", "../src/_shaders/FragmentShader.glsl");
    boxShader = Shader("../src/_shaders/VertexShader.glsl", "../src/_shaders/BoxShader.glsl");


    /* ---- game objects ----*/
    player = Creature(-1.0f, 0.0f, 0.0f, true);
    enemy = Creature(1.0f, 0.0f, 0.0f, false);
    box = Obstacle(0.0f, 0.0f, 0.0f);

    /* ---- vertex buffer data and vertex attribute config ---- */
    generateVertexObjects(&player);
    generateVertexObjects(&enemy);
    generateVertexObjects(&box);


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
    texData = stbi_load("../assets/awesomeface.png", &width, &height, &nChannels, 0);
    glGenTextures(1, &faceTex);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, faceTex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(texData);

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
}

void Game::run() {
    // bind textures
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, boxTex);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, shipTex);

    while(!glfwWindowShouldClose(window)) {
        glClearColor(.1f, .2f, .2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // calculate time delta
        float frameT = glfwGetTime();
        deltaT = frameT - lastFrameT;
        lastFrameT = frameT;

        // user input and calculations
        processInput(window);

        // model matrix, used for local object positions
        glm::mat4 model(1.0f);

        // view matrix, used for world coordinate space
        glm::mat4 view = camera.getView();

        // projection matrix (perspective not ortho)
        glm::mat4 projection(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.0f);


        // render player
        playerShader.use();
        playerShader.setMat4("model", model);
        playerShader.setMat4("view", view);
        playerShader.setMat4("projection", projection);
        glBindVertexArray(player.VAO);
        glDrawArrays(GL_TRIANGLES, 0, player.modelSize);


        // render enemy
        enemyShader.use();
        playerShader.setMat4("model", model);
        playerShader.setMat4("view", view);
        playerShader.setMat4("projection", projection);
        glBindVertexArray(enemy.VAO);
        glDrawArrays(GL_TRIANGLES, 0, enemy.modelSize);


        // render box
        boxShader.use();
        playerShader.setMat4("model", model);
        playerShader.setMat4("view", view);
        playerShader.setMat4("projection", projection);
        glBindVertexArray(box.VAO);
        glDrawArrays(GL_TRIANGLES, 0, box.modelSize);


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

void Game::generateVertexObjects(GameObject* object) {
    /* ---- vertex buffer data and vertex attribute config ---- */
    //use a vertex array object to store VBO configurations
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    object->VBO = VBO;
    object->VAO = VAO;
    glBufferData(GL_ARRAY_BUFFER, object->modelSize * sizeof(Vertex), object->modelVerts, GL_DYNAMIC_DRAW);
    // describe VERTEX POSITIONS
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // describe VERTEX COLORS
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // describe TEXTURE COORDINATES
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    // unbind VAO and VBO
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


int Game::processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    // position
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        player.coordY += deltaT * player.getSpeed();
        camera.cameraPos += deltaT * player.getSpeed() * camera.cameraFront;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        player.coordY -= deltaT * player.getSpeed();
        camera.cameraPos -= deltaT * player.getSpeed() * camera.cameraFront;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        player.coordX -= deltaT * player.getSpeed();
        camera.cameraPos -= deltaT * player.getSpeed() * camera.cameraRight;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        player.coordX += deltaT * player.getSpeed();
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

void Game::spawnBullet(int side) {
    float tipX, tipY;
    int vHor = -1;

    if (side == PLAYER) {
        tipX = player.modelVerts[0].x;
        tipY = player.modelVerts[0].y;
        if (player.direction == LEFT)
            vHor = LEFT;
        else if (player.direction == RIGHT)
            vHor = RIGHT;
    }
    else if (side == ENEMY) {
        tipX = enemy.modelVerts[0].x;
        tipY = enemy.modelVerts[0].y;
        if (enemy.direction == LEFT)
            vHor = LEFT;
        else if (enemy.direction == RIGHT)
            vHor = RIGHT;
    }
    else {
        std::cout << "INVALID BULLET SPAWN" << std::endl;
        return;
    }

    Vertex bulletModel [] = {
            // Vertex Coordinates              // Colors         // 2D Texture Coords
            {tipX - 0.01f, tipY - 0.04f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f},
            {tipX + 0.01f, tipY + 0.04f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f},
            {tipX - 0.01f, tipY + 0.04f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f},

            {tipX - 0.01f, tipY - 0.04f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f},
            {tipX + 0.01f, tipY - 0.04f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f},
            {tipX + 0.01f, tipY + 0.04f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f},
    };
    Bullet bul(bulletModel, side, vHor);
    generateVertexObjects(&bul);
    bullets.push_back(bul);
}

void Game::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Game::mouse_callback(GLFWwindow* window, double x, double y) {
    // calculate mouse offset change
    float dX = x - lastMouseX;
    float dY = y - lastMouseY;
    lastMouseX = x;
    lastMouseY = y;

    float sensitivity = 0.03f;
    dX *= sensitivity;
    dY *= sensitivity;


    // add offset value to camera yaw/pitch
    camera.pitch -= dY;
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
}