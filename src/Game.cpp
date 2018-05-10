//
// Created by leo on 2/6/18.
//

#include "Game.h"

static const float RAD_TO_DEG  = 57.295779513f;


Game::Game(bool debug)
{
    std::cout << "Initializing..." << std::endl;
    glfwInit(); // create window
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Dylan's Game", nullptr, nullptr);
    glfwSetWindowPos(window, 50, 0);
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


    // light sources
    LightSource sun(glm::vec3(2.0f, 10.0f, 2.0f), glm::vec3(0.05f), boxModel, LIGHTSOURCE_LOW_INTENSITY, glm::vec3(.9f, .8f, .7f), 'N');
    sun.lDirection = glm::vec3(-2.0f, -1.0f, -2.0f);
    directionalLights.push_back(sun);

    srand((unsigned int)glfwGetTime());
    int bound = 10;
    char orbits [] = {'X', 'Y', 'Z'};

    for (int i = 0; i < 10; i++) {
        glm::vec3 randPos(rand() % bound, rand() % (bound / 2), rand() % bound);
        glm::vec3 randColor((rand() % 100) / 100.0f, (rand() % 100) / 100.0f, (rand() % 100) / 100.0f);
        LightSource light(randPos, glm::vec3(0.1f), boxModel, LIGHTSOURCE_HIGH_INTENSITY, randColor, orbits[rand() % 3]);
        pointLights.push_back(light);
    }


    LightSource flashLight(camera.cameraPos, glm::vec3(0.05f), boxModel, LIGHTSOURCE_STD_INTENSITY, glm::vec3(.7f, .7f, .9f), 'N');
    flashLight.lDirection = camera.cameraTarget;
    spotLights.push_back(flashLight);



    /* ---- game logic initialization ---- */
    lastMouseX = SCR_WIDTH / 2;
    lastMouseY = SCR_HEIGHT / 2;
    firstMouseInput = true;
    flashlightCooldown = 0.0f;
    playerBulletCooldown = 0.0f;

    leapController.enableGesture(Leap::Gesture::TYPE_CIRCLE);
    leapController.enableGesture(Leap::Gesture::TYPE_SWIPE);
    leapController.enableGesture(Leap::Gesture::TYPE_KEY_TAP);

//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, object.position);
    model = glm::rotate(model, -glm::radians(object.yaw), object.modelUp);
    model = glm::rotate(model, glm::radians(object.pitch), object.modelRight);
    model = glm::scale(model, object.scale);

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

    /* LEAP MOTION PROCESSING */
    if (leapController.isConnected()) {
        Leap::Frame cFrame = leapController.frame();

        // Process gesture data
        Leap::GestureList gestures = cFrame.gestures();
        for (Leap::GestureList::const_iterator gl = gestures.begin(); gl != gestures.end(); ++gl) {
            Leap::Gesture gesture = *gl;

            if (gesture.type() == Leap::Gesture::TYPE_CIRCLE) {
                Leap::CircleGesture circle = gesture;
                std::string clockwiseness;

                if (circle.pointable().direction().angleTo(circle.normal()) <= M_PI/2) {
                    clockwiseness = "clockwise";
                } else {
                    clockwiseness = "counterclockwise";
                }


                if (circle.state() == Leap::Gesture::STATE_STOP && circle.progress() >= 1.0f) {
                    if (clockwiseness == "clockwise") {
                        for (auto &obj: pointLights) {
                            if (obj.rotAxis == 'X')
                                obj.rotAxis = 'Y';
                            if (obj.rotAxis == 'Y')
                                obj.rotAxis = 'Z';
                            if (obj.rotAxis == 'Z')
                                obj.rotAxis = 'X';
                        }
                    }
                    else if (clockwiseness == "counterclockwise") {
                        for (auto &obj: pointLights) {
                            if (obj.rotAxis == 'Z')
                                obj.rotAxis = 'Y';
                            if (obj.rotAxis == 'Y')
                                obj.rotAxis = 'X';
                            if (obj.rotAxis == 'X')
                                obj.rotAxis = 'Z';
                        }
                    }
                }
            }
            else if (gesture.type() == Leap::Gesture::TYPE_SWIPE) {
                Leap::SwipeGesture swipe = gesture;
                if (swipe.state() == Leap::Gesture::STATE_STOP) {
                    std::cout << "swiped: ";
                    float vX = swipe.direction().x;
                    float speed = swipe.speed();
                    if (vX > 0) {
                        std::cout << "right" << std::endl;
                        for (auto &obj: pointLights) {
                            obj.speed = 25.0f;
                            obj.rotAxis = 'Y';
                        }
                    }
                    else if (vX < 0) {
                        std::cout << "left" << std::endl;
                        for (auto &obj: pointLights) {
                            obj.speed = -25.0f;
                            obj.rotAxis = 'Y';
                        }
                    }

                }

            }
            else if (gesture.type() == Leap::Gesture::TYPE_KEY_TAP) {
                Leap::KeyTapGesture tap = gesture;
                if (tap.isValid() && tap.state() == Leap::Gesture::STATE_STOP) {
                    std::cout << "-------KeyTap-------" << std::endl
                            << "Id: " << tap.id()
                            << "\tFinger: " << tap.pointable().id()
                            << "\tDirection: " << tap.direction()
                            << "\tProgress: " << tap.progress()
                            << std::endl;

                }
            }
        }


        // Process Hand data
//        Leap::HandList hands = cFrame.hands();
//        for (Leap::HandList::const_iterator hl = hands.begin(); hl != hands.end(); ++hl) {
//            Leap::Hand hand = *hl;
//            // Get the hand's normal vector and direction
//            const Leap::Vector normal = hand.palmNormal();
//            const Leap::Vector direction = hand.direction();
//
//            // Calculate the hand's pitch, roll, and yaw angles
//            float tiltFactor = 2.0f;
//            if (normal.roll() * RAD_TO_DEG > 30) {
//                for (auto &obj: creatures) {
//                    obj.rotateFace(-deltaT * obj.getTurnSpeed());
//                }
//            } else if (normal.roll() * RAD_TO_DEG < -20) {
//                for (auto &obj: creatures) {
//                    obj.rotateFace(deltaT * obj.getTurnSpeed());
//                }
//            }
//
//            if (direction.pitch() * RAD_TO_DEG < 15) {
//                for (auto &obj: creatures) {
//                    obj.position += deltaT * obj.getSpeed() * obj.modelFront;
//                }
//            } else if (direction.pitch() * RAD_TO_DEG > 60) {
//                for (auto &obj: creatures) {
//                    obj.position -= deltaT * obj.getSpeed() * obj.modelFront;
//                }
//            }
//        }
    }

    /* KEYBOARD INPUT PROCESSING */
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        for (auto &obj: creatures) {
            obj.position += deltaT * obj.getSpeed() * obj.modelFront;
            obj.printPos();
        }
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        for (auto &obj: creatures) {
            obj.position -= deltaT * obj.getSpeed() * obj.modelFront;
            obj.printPos();
        }
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        for (auto &obj: creatures) {
            obj.rotateFace(-deltaT * obj.getTurnSpeed());
            obj.printFacing();
        }
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        for (auto &obj: creatures) {
            obj.rotateFace(deltaT * obj.getTurnSpeed());
            obj.printFacing();
        }
    }

    /* CAMERA REPOSITIONING */
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        camera.cameraPos += deltaT * CAMERA_SPEED * camera.cameraUp;
        spotLights[0].position = camera.cameraPos;
    }
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
        camera.cameraPos -= deltaT * CAMERA_SPEED * camera.cameraUp;
        spotLights[0].position = camera.cameraPos;
    }
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
                spotLights.at(0).setIntensity(LIGHTSOURCE_STD_INTENSITY);
            }
            else {
                spotLights.at(0).setIntensity(glm::vec3(0.0f));
            }
        }
    }

    return -1;
}


void Game::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Game::moveCameraView(double dX, double dY) {
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
