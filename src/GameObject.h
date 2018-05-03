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
    :pitch(0.0f), yaw(-90.0f) {
        this->position = position;
        this->scale = scale;
        this->model = Model(modelPath);
        material.shininess = 64;
        material.ambient = glm::vec3(0.5f);
        material.diffuse = glm::vec3(0.9f);
        material.specular = glm::vec3(1.0f);
        modelFront = glm::vec3(0.0f, 0.0f, -1.0f);
        modelUp = glm::vec3(0.0f, 1.0f, 0.0f);
        modelRight = glm::normalize(glm::cross(glm::vec3(.0f, 1.0f, .0f), modelFront));

    };


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
