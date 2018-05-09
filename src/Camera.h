//
// Created by leo on 3/6/18.
//

#ifndef TEXTGAME_CAMERA_H
#define TEXTGAME_CAMERA_H


#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

const float YAW         =  -90.0f;
const float PITCH       =  0.0f;
const float CAMERA_SPEED       =  2.5f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;
const glm::vec3 WORLD_UP = glm::vec3(0.0f, 1.0f, 0.0f);

class Camera {
public:
    Camera(): pitch(PITCH), yaw(YAW), sensitivity(SENSITIVITY){
        std::cout << "Default Camera instantiated" << std::endl;
        // Gram-Schmidt process to get camera coordinate space
        cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
        cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
        cameraDir = glm::normalize(cameraPos - cameraTarget);
        cameraRight = glm::normalize(glm::cross(glm::vec3(.0f, 1.0f, .0f), cameraDir));
        cameraUp = WORLD_UP;
        cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    }

    // Constructor with vectors
    Camera(glm::vec3 position, glm::vec3 up, float yaw_g = YAW, float pitch_g = PITCH) : cameraFront(glm::vec3(0.0f, 0.0f, -1.0f)), sensitivity(SENSITIVITY)
    {
        cameraPos = position;
        cameraUp = up;
        yaw = yaw_g;
        pitch = pitch_g;
    }

    glm::mat4 getView() {
        return glm::lookAt(
                cameraPos,
                cameraPos + cameraFront,
                cameraUp
        );
    }

    glm::vec3 cameraPos;
    glm::vec3 cameraTarget;
    glm::vec3 cameraDir;
    glm::vec3 cameraRight;
    glm::vec3 cameraUp;
    glm::vec3 cameraFront;

    float pitch;
    float yaw;
    float sensitivity;
};


#endif //TEXTGAME_CAMERA_H
