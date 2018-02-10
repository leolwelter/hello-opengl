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

    //init window
    if (window == NULL) {
        std::cout << "GL Borked :(" << std::endl;
        glfwTerminate();
        return;
    }

    //init GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "GLAD Borked :(" << std::endl;
        return;
    }

    //now we can work with gl functions
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);


    /* ---- SHADER SOURCE AND COMPILATION ---- */
    // VERTEX SHADER
    const char* vertexShaderSource = "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "\n"
            "void main()\n"
            "{\n"
            "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
            "}";
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    //check for compilation errors
    int compSucces;
    char log[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compSucces);
    if (!compSucces) {
        glGetShaderInfoLog(vertexShader, 512, NULL, log);
        std::cout << "ERROR COMPILING VERTEX SHADER:\n" << log << std::endl;
    }

    // FRAGMENT SHADER - ORANGE
    const char* fragmentShaderSource = "\n"
            "#version 330 core\n"
            "out vec4 FragColor;\n"
            "\n"
            "void main()\n"
            "{\n"
            "    FragColor = vec4(0.4f, 0.4f, 1.0f, 1.0f);\n"
            "} ";
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    //check for compilation errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compSucces);
    if (!compSucces) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, log);
        std::cout << "ERROR COMPILING FRAGMENT SHADER\n" << log << std::endl;
    }

    // link PLAYER shader
    playerShader = glCreateProgram();
    glAttachShader(playerShader, vertexShader);
    glAttachShader(playerShader, fragmentShader);
    glLinkProgram(playerShader);

    //check for linking errors
    glGetProgramiv(playerShader, GL_LINK_STATUS, &compSucces);
    if (!compSucces) {
        glGetProgramInfoLog(playerShader, 512, NULL, log);
        std::cout << "ERROR LINKING SHADER PROGRAM\n" << log << std::endl;
    }

    // shader for enemy models
    fragmentShaderSource = "\n"
            "#version 330 core\n"
            "out vec4 FragColor;\n"
            "\n"
            "void main()\n"
            "{\n"
            "    FragColor = vec4(1.0f, 0.4f, 0.4f, 1.0f);\n"
            "} ";
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    //check for compilation errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compSucces);
    if (!compSucces) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, log);
        std::cout << "ERROR COMPILING FRAGMENT SHADER\n" << log << std::endl;
    }

    // link ENEMY shader
    enemyShader = glCreateProgram();
    glAttachShader(enemyShader, vertexShader);
    glAttachShader(enemyShader, fragmentShader);
    glLinkProgram(enemyShader);

    //check for linking errors
    glGetProgramiv(enemyShader, GL_LINK_STATUS, &compSucces);
    if (!compSucces) {
        glGetProgramInfoLog(enemyShader, 512, NULL, log);
        std::cout << "ERROR LINKING SHADER PROGRAM\n" << log << std::endl;
    }


    // BULLET shader
    fragmentShaderSource = "\n"
            "#version 330 core\n"
            "out vec4 FragColor;\n"
            "\n"
            "void main()\n"
            "{\n"
            "    FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
            "} ";
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    //check for compilation errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compSucces);
    if (!compSucces) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, log);
        std::cout << "ERROR COMPILING FRAGMENT SHADER\n" << log << std::endl;
    }

    // link ENEMY shader
    bulletShader = glCreateProgram();
    glAttachShader(bulletShader, vertexShader);
    glAttachShader(bulletShader, fragmentShader);
    glLinkProgram(bulletShader);

    //check for linking errors
    glGetProgramiv(bulletShader, GL_LINK_STATUS, &compSucces);
    if (!compSucces) {
        glGetProgramInfoLog(bulletShader, 512, NULL, log);
        std::cout << "ERROR LINKING SHADER PROGRAM\n" << log << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(bulletShader);

    /* ---- game objects ----*/

    Vertex enemyModel [] = {
            {0.3f, 0.0f, 0.0f},
            {0.7f, 0.0f, 0.0f},
            {0.5f, 0.4f, 0.0f},
    };
    player = Creature();
    enemy = Creature(enemyModel);


    /* ---- vertex buffer data and vertex attribute config ---- */
    generateVertexObjects(&player);
    generateVertexObjects(&enemy);
}

void Game::run() {
    //render in a loop
    while(!glfwWindowShouldClose(window)) {
        glClearColor(.1f, .2f, .2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        processInput(window);
        if (player.direction != -1) {
            player.move(player.direction);
            // bind and reload player model
            getModelVertices(&player);
        }

        if (enemy.direction != -1) {
            enemy.move(enemy.direction);
            // bind and reload ENEMY model
            getModelVertices(&enemy);
        }

        glUseProgram(playerShader);
        glBindVertexArray(player.VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(enemyShader);
        glBindVertexArray(enemy.VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

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

void Game::getModelVertices(GameObject* object) {
    glBindVertexArray(object->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, object->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(object->modelVerts), object->modelVerts, GL_DYNAMIC_DRAW);

}

int Game::processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
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
    return -1;
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

    glBufferData(GL_ARRAY_BUFFER, sizeof(object->modelVerts), object->modelVerts, GL_DYNAMIC_DRAW);
    //specify how our vertex data is arranged
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // unbind VAO and VBO
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Game::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    std::cout << "Resizing: " << width << " , " << height << std::endl;
}