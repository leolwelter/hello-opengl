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
#include "Shader.h"

enum DIRECTION {
    UP, LEFT, DOWN, RIGHT
};

struct Material {
    float shininess;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

struct Vertex {
    float x, y, z;
    float red, green, blue;
    float texX, texY;
    float normX, normY, normZ;
};



class GameObject {
public:
    // constructors
    GameObject();
    GameObject(float x, float y, float z, int mSize);

    // attributes
    unsigned int VBO;
    unsigned int VAO;
    Vertex* modelVerts; //model vertex data
    int modelSize;
    float coordX;
    float coordY;
    float coordZ;
    glm::vec3 scale;
    Shader shader;
    Material material;

    // methods
    void generateVertexObjects(void);
    glm::vec3 getPos();
};


#endif //TEXTGAME_GAMEOBJECT_H
