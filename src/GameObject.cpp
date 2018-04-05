//
// Created by leo on 2/10/18.
//

#include "GameObject.h"
#include <iostream>

GameObject::GameObject()
{
    std::cout << "DEFAULT OBJECT CONSTRUCTED" << std::endl;
}

GameObject::GameObject(float x, float y, float z, int mSize)
        : coordX(x), coordY(y), coordZ(z), modelSize(mSize)
{
    std::cout << "NEW OBJECT: [" << x << ", " << y << ", " << z << "]" << std::endl;
    modelVerts = (Vertex*)malloc(mSize * sizeof(Vertex));
    scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

GameObject::GameObject(Vertex* vertexData, int mSize) {
    modelSize = mSize;
    modelVerts = (Vertex*)malloc(mSize * sizeof(Vertex));
    for (int i = 0; i < mSize; i++) {
        modelVerts[i] = vertexData[i];
    }
}

glm::mat4 GameObject::reset() {
    glm::mat4 trans(1.0f);
    trans = glm::translate(trans, glm::vec3(coordX, coordY, coordZ));
    return trans;
}

glm::vec3 GameObject::getPos() {
    glm::vec3 lpos = glm::vec3(coordX, coordY, coordZ);
    return lpos;
}