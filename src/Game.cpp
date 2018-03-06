//
// Created by leo on 2/6/18.
//

#include "Game.h"

Game::Game() {
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
    player = Creature(0.0f, 0.0f, true);
    enemy = Creature(0.0f, 0.0f, false);
    box = Obstacle(0.0f, 0.0f);

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

        processInput(window);

        // model matrix, used for local object positions
        glm::mat4 model(1.0f);
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.0f, 1.0f, .0f));

        // view matrix, used for world coordinate space
        glm::mat4 view(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

        // projection matrix (perspective not ortho)
        glm::mat4 projection(1.0f);
        projection = glm::perspective(glm::radians(60.0f), (float)SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.0f);


        // move player
        glm::mat4 transform(1.0f);
        if (player.direction == UP) {
            player.coordY += player.getSpeed();
        }
        else if (player.direction == LEFT) {
            player.coordX += -player.getSpeed();
        }
        else if (player.direction == RIGHT) {
            player.coordX += player.getSpeed();
        }
        else if (player.direction == DOWN) {
            player.coordY += -player.getSpeed();
        }
        transform = glm::translate(transform, glm::vec3(player.coordX, player.coordY, 0.0f));

        // render player
        playerShader.use();
        playerShader.setMat4("model", model);
        playerShader.setMat4("view", view);
        playerShader.setMat4("projection", projection);

        glBindVertexArray(player.VAO);
        glDrawArrays(GL_TRIANGLES, 0, player.modelSize);


        // move enemy
        if (enemy.direction == UP) {
            enemy.coordY += enemy.getSpeed();
        }
        else if (enemy.direction == LEFT) {
            enemy.coordX += -enemy.getSpeed();
        }
        else if (enemy.direction == RIGHT) {
            enemy.coordX += enemy.getSpeed();
        }
        else if (enemy.direction == DOWN) {
            enemy.coordY += -enemy.getSpeed();
        }

        // render enemy
        enemyShader.use();
        playerShader.setMat4("model", model);
        playerShader.setMat4("view", view);
        playerShader.setMat4("projection", projection);
        glBindVertexArray(enemy.VAO);
        glDrawArrays(GL_TRIANGLES, 0, enemy.modelSize);

        // move box

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

void Game::getModelVertices(GameObject* object) {
    glBindVertexArray(object->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, object->VBO);
    glBufferData(GL_ARRAY_BUFFER, object->modelSize * sizeof(Vertex), object->modelVerts, GL_DYNAMIC_DRAW);
}

int Game::processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        enemy.direction =  UP;
    }
    else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        enemy.direction = DOWN;
    }
    else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        enemy.direction = LEFT;
    }
    else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        enemy.direction = RIGHT;
    }
    else {
        enemy.direction = -1;
    }


    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        player.direction =  UP;
    }
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        player.direction = DOWN;
    }
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        player.direction = LEFT;
    }
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        player.direction = RIGHT;
    }
    else {
        player.direction = -1;
    }


    if ((glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) && playerCooldown()) {
        spawnBullet(PLAYER);
        lastPlayerShotTime = glfwGetTime();
    }
    if ((glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) && enemyCooldown()) {
        spawnBullet(ENEMY);
        lastEnemyShotTime = glfwGetTime();
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