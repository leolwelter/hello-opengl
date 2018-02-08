#include "Game.h"


int main(int argc, char** argv) {
    Game game;
    game.run();
}


//std::cout << "Initializing..." << std::endl;
//
//glfwInit(); // create window
//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Dylan's Game", nullptr, nullptr);
//glfwMakeContextCurrent(window);
//
////init window
//if (window == NULL) {
//std::cout << "GL Borked :(" << std::endl;
//glfwTerminate();
//return -1;
//}
//
////init GLAD
//if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
//std::cout << "GLAD Borked :(" << std::endl;
//return -1;
//}
//
////now we can work with gl functions
//glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
//
////register callback functions
//glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//
//
///* ---- SHADER SOURCE AND COMPILATION ---- */
////TODO: put in GameEngine
//const char* vertexShaderSource = "#version 330 core\n"
//        "layout (location = 0) in vec3 aPos;\n"
//        "\n"
//        "void main()\n"
//        "{\n"
//        "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//        "}";
//unsigned int vertexShader;
//vertexShader = glCreateShader(GL_VERTEX_SHADER);
//glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//glCompileShader(vertexShader);
//
////check for compilation errors
//int compSucces;
//char log[512];
//glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compSucces);
//if (!compSucces) {
//glGetShaderInfoLog(vertexShader, 512, NULL, log);
//std::cout << "ERROR COMPILING VERTEX SHADER:\n" << log << std::endl;
//}
//
//const char* fragmentShaderSource = "\n"
//        "#version 330 core\n"
//        "out vec4 FragColor;\n"
//        "\n"
//        "void main()\n"
//        "{\n"
//        "    FragColor = vec4(1.0f, 0.8f, 0.3f, 1.0f);\n"
//        "} ";
//unsigned int fragmentShader;
//fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//glCompileShader(fragmentShader);
//
////check for compilation errors
//glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compSucces);
//if (!compSucces) {
//glGetShaderInfoLog(fragmentShader, 512, NULL, log);
//std::cout << "ERROR COMPILING FRAGMENT SHADER\n" << log << std::endl;
//}
//
////create a program to link the compiled shaders together
//unsigned int playerShader;
//playerShader = glCreateProgram();
//glAttachShader(playerShader, vertexShader);
//glAttachShader(playerShader, fragmentShader);
//glLinkProgram(playerShader);
//
////check for linking errors
//glGetProgramiv(playerShader, GL_LINK_STATUS, &compSucces);
//if (!compSucces) {
//glGetProgramInfoLog(playerShader, 512, NULL, log);
//std::cout << "ERROR LINKING SHADER PROGRAM\n" << log << std::endl;
//}
//
//glUseProgram(playerShader);
//glDeleteShader(vertexShader);
//glDeleteShader(fragmentShader);
//
///* ---- vertex buffer data and vertex attribute config ---- */
//Creature player = Creature();
//
////use a vertex array object to store later configuration calls
////related to our VBO; we unbind after configuring
//unsigned int VAO;
//glGenVertexArrays(1, &VAO);
//glBindVertexArray(VAO);
//
////generate a buffer ID for model vertex data
//unsigned int VBO;
//glGenBuffers(1, &VBO);
//glBindBuffer(GL_ARRAY_BUFFER, VBO);
//
////specify how our vertex data is arranged
//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//glEnableVertexAttribArray(0);
//getModelVertices(VAO, VBO, player);
//
//
////render in a loop
//int dir;
//while(!glfwWindowShouldClose(window)) {
//glClearColor(.1f, .2f, .2f, 1.0f);
//glClear(GL_COLOR_BUFFER_BIT);
//dir = processInput(window);
//if (dir != -1) {
//player.move(dir);
//getModelVertices(VAO, VBO, player);
//}
//
//glUseProgram(playerShader);
//glBindVertexArray(VAO);
//glDrawArrays(GL_TRIANGLES, 0, 3);
//
//glfwSwapBuffers(window);
//glfwPollEvents();
//}
//return 0;