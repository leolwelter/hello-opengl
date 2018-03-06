//
// Created by leo on 3/6/18.
//

#ifndef TEXTGAME_CAMERA_H
#define TEXTGAME_CAMERA_H


#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    Camera(): pitch(0.0f), yaw(0.0f) {
        // Gram-Schmidt process to get camera coordinate space
        cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
        cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
        cameraDir = glm::normalize(cameraPos - cameraTarget);
        cameraRight = glm::normalize(glm::cross(glm::vec3(.0f, 1.0f, .0f), cameraDir));
        cameraUp = glm::normalize(glm::cross(cameraDir, cameraRight));
        cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
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
};


#endif //TEXTGAME_CAMERA_H
