//
// Created by leo on 2/10/18.
//

#include "GameObject.h"

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

void GameObject::generateVertexObjects() {
    /* ---- vertex buffer data and vertex attribute config ---- */
    //use a vertex array object to store VBO configurations
    unsigned int tmpVAO, tmpVBO;
    glGenVertexArrays(1, &tmpVAO);
    glGenBuffers(1, &tmpVBO);

    glBindVertexArray(tmpVAO);
    glBindBuffer(GL_ARRAY_BUFFER, tmpVBO);

    VBO = tmpVBO;
    VAO = tmpVAO;

    glBufferData(GL_ARRAY_BUFFER, modelSize * sizeof(Vertex), modelVerts, GL_DYNAMIC_DRAW);
    // describe VERTEX POSITIONS
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // describe VERTEX COLORS
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // describe TEXTURE COORDINATES
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    // describe NORMAL VECTORS
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));
    glEnableVertexAttribArray(3);
    // unbind VAO and VBO
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

glm::vec3 GameObject::getPos() {
    glm::vec3 lpos = glm::vec3(coordX, coordY, coordZ);
    return lpos;
}