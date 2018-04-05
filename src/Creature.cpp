//
// Created by leo on 2/4/18.
//

#include "Creature.h"

static const Vertex defaultPlayerModel [] = {
        // front face
        { 0.0f, 1.0f,  0.0f, 0.7f, 0.6f, 0.8f, .0f, .0f,   0.0f, 0.3f,  0.7f}, //tip
        {-1.0f, 0.0f,  1.0f, 0.7f, 0.6f, 0.8f, .0f, .0f,   0.0f, 0.3f,  0.7f}, //top left base
        { 1.0f, 0.0f,  1.0f, 0.7f, 0.6f, 0.8f, .0f, .0f,   0.0f, 0.3f,  0.7f}, //top right base
        // right face
        { 0.0f, 1.0f,  0.0f, 0.7f, 0.6f, 0.8f, .0f, .0f,  0.7f, 0.3f,  0.0f}, //tip
        { 1.0f, 0.0f,  1.0f, 0.7f, 0.6f, 0.8f, .0f, .0f,  0.7f, 0.3f,  0.0f}, //top right base
        { 1.0f, 0.0f, -1.0f, 0.7f, 0.6f, 0.8f, .0f, .0f,  0.7f, 0.3f,  0.0f}, //bottom right base
        // left face
        { 0.0f, 1.0f,  0.0f, 0.7f, 0.6f, 0.8f, .0f, .0f, -0.7f, 0.3f,  0.0f}, //tip
        {-1.0f, 0.0f, -1.0f, 0.7f, 0.6f, 0.8f, .0f, .0f, -0.7f, 0.3f,  0.0f}, //bottom left base
        {-1.0f, 0.0f,  1.0f, 0.7f, 0.6f, 0.8f, .0f, .0f, -0.7f, 0.3f,  0.0f}, //top left base
        // back face
        { 0.0f, 1.0f,  0.0f, 0.7f, 0.6f, 0.8f, .0f, .0f,  0.0f, 0.3f, -0.7f}, //tip
        { 1.0f, 0.0f, -1.0f, 0.7f, 0.6f, 0.8f, .0f, .0f,  0.0f, 0.3f, -0.7f}, //bottom right base
        {-1.0f, 0.0f, -1.0f, 0.7f, 0.6f, 0.8f, .0f, .0f,  0.0f, 0.3f, -0.7f}, //bottom left base
        // 1/2 base
        {-1.0f, 0.0f,  1.0f, 0.7f, 0.6f, 0.8f, .0f, .0f,  0.0f, -1.0f, 0.0f}, //top left base
        { 1.0f, 0.0f,  1.0f, 0.7f, 0.6f, 0.8f, .0f, .0f,  0.0f, -1.0f, 0.0f}, //top right base
        {-1.0f, 0.0f, -1.0f, 0.7f, 0.6f, 0.8f, .0f, .0f,  0.0f, -1.0f, 0.0f}, //bottom left base
        // 2/2 base
        { 1.0f, 0.0f, -1.0f, 0.7f, 0.6f, 0.8f, .0f, .0f,  0.0f, -1.0f, 0.0f}, //bottom right base
        {-1.0f, 0.0f, -1.0f, 0.7f, 0.6f, 0.8f, .0f, .0f,  0.0f, -1.0f, 0.0f}, //bottom left base
        { 1.0f, 0.0f,  1.0f, 0.7f, 0.6f, 0.8f, .0f, .0f,  0.0f, -1.0f, 0.0f}, //top right base
};

Creature::Creature()
        :hp(0), attack(0), defense(0), speed(0)
{
}

Creature::Creature(float x, float y, float z)
        :hp(0), attack(0), defense(0), speed(3.0f), GameObject(x, y, z, 15)
{
    for (int i = 0; i < modelSize; i++) {
        modelVerts[i] = defaultPlayerModel[i];
    }
    scale = glm::vec3(0.2f, 0.2f, 0.2f);
}



glm::mat4 Creature::move(float dx, float dy, float dz) {
    coordX += dx;
    coordY += dy;
    coordZ += dz;
    glm::mat4 trans(1.0f);
    trans = glm::translate(trans, glm::vec3(dx, dy, dz));
    return trans;
}


glm::mat4 Creature::move(int direction) {
    glm::mat4 trans(1.0f);
    switch (direction) {
        case UP:
            trans = glm::translate(trans, glm::vec3(coordX, 0.01f + coordY, coordZ));
            coordY += 0.01f;
            break;
        case DOWN:
            trans = glm::translate(trans, glm::vec3(coordX, -0.01f + coordY, coordZ));
            coordY -= 0.01f;
            break;
        case LEFT:
            trans = glm::translate(trans, glm::vec3(-0.01f + coordX, coordY, coordZ));
            coordX -= 0.01f;
            break;
        case RIGHT:
            trans = glm::translate(trans, glm::vec3(0.01f + coordX, coordY, coordZ));
            coordX += 0.01f;
            break;
        default:
            std::cout << "INVALID MOVEMENT" << std::endl;
            break;
    }
    return trans;
}
