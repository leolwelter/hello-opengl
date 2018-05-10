//
// Created by leo on 2/10/18.
//

#ifndef TEXTGAME_GAMEOBJECT_H
#define TEXTGAME_GAMEOBJECT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Shader.h"
#include "Model.h"
#include "Camera.h"

enum DIRECTION {
    UP, LEFT, DOWN, RIGHT
};

struct Material {
    float shininess;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};


class GameObject {
public:
    GameObject(glm::vec3 position, glm::vec3 scale, char* modelPath)
    :pitch(0.0f), yaw(0.0f) {
        this->position = position;
        this->scale = scale;
        this->model = Model(modelPath);
        material.shininess = 64;
        material.ambient = glm::vec3(0.5f);
        material.diffuse = glm::vec3(0.9f);
        material.specular = glm::vec3(1.0f);

        shader = Shader("../src/_shaders/VertexShader.glsl", "../src/_shaders/FragmentShader.glsl");

        float faceX = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
        float faceY = sin(glm::radians(pitch));
        float faceZ = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
        modelFront = glm::normalize(glm::vec3(faceX, faceY, faceZ));
        modelUp = WORLD_UP;
        modelRight = glm::normalize(glm::cross(modelFront, modelUp));

    }

    GameObject() {};

    glm::mat4 getFacing() {
            return glm::lookAt(
                    position,
                    position + modelFront,
                    modelUp
            );
    }

    void rotateFace(double dYaw) {
        yaw += dYaw;
        float faceX = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
        float faceY = sin(glm::radians(pitch));
        float faceZ = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
        modelFront = glm::normalize(glm::vec3(faceX, faceY, faceZ));
        modelRight = glm::normalize(glm::cross(modelFront, modelUp));
    }

    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 modelFront;
    glm::vec3 modelRight;
    glm::vec3 modelUp;
    float pitch;
    float yaw;
    Material material;
    Shader shader;
    Model model;
};


#endif //TEXTGAME_GAMEOBJECT_H
