//
// Created by leo on 2/4/18.
//

#include "Creature.h"

static const Vertex defaultModelElements [] = {
    {-1.0f, 0.0f,  1.0f, .0f, .0f, 1.0f, .0f, .0f}, //top left base
    { 1.0f, 0.0f,  1.0f, .0f, .0f, 1.0f, .0f, .0f}, //top right base
    {-1.0f, 0.0f, -1.0f, .0f, .0f, 1.0f, .0f, .0f}, //bottom left base
    { 1.0f, 0.0f, -1.0f, .0f, .0f, 1.0f, .0f, .0f}, //bottom right base
    { 0.0f, 1.0f,  0.0f, .0f, .0f, 1.0f, .0f, .0f}, //tip
};

static const Vertex defaultPlayerModel [] = {
        // front face
        { 0.0f, 1.0f,  0.0f, .0f, .0f, 1.0f, .0f, .0f}, //tip
        {-1.0f, 0.0f,  1.0f, .0f, .0f, 1.0f, .0f, .0f}, //top left base
        { 1.0f, 0.0f,  1.0f, .0f, .0f, 1.0f, .0f, .0f}, //top right base
        // right face
        { 0.0f, 1.0f,  0.0f, .0f, .0f, 1.0f, .0f, .0f}, //tip
        { 1.0f, 0.0f,  1.0f, .0f, .0f, 1.0f, .0f, .0f}, //top right base
        { 1.0f, 0.0f, -1.0f, .0f, .0f, 1.0f, .0f, .0f}, //bottom right base
        // left face
        { 0.0f, 1.0f,  0.0f, .0f, .0f, 1.0f, .0f, .0f}, //tip
        {-1.0f, 0.0f, -1.0f, .0f, .0f, 1.0f, .0f, .0f}, //bottom left base
        {-1.0f, 0.0f,  1.0f, .0f, .0f, 1.0f, .0f, .0f}, //top left base
        // back face
        { 0.0f, 1.0f,  0.0f, .0f, .0f, 1.0f, .0f, .0f}, //tip
        { 1.0f, 0.0f, -1.0f, .0f, .0f, 1.0f, .0f, .0f}, //bottom right base
        {-1.0f, 0.0f, -1.0f, .0f, .0f, 1.0f, .0f, .0f}, //bottom left base
        // 1/2 base
        {-1.0f, 0.0f,  1.0f, .0f, .0f, 1.0f, .0f, .0f}, //top left base
        { 1.0f, 0.0f,  1.0f, .0f, .0f, 1.0f, .0f, .0f}, //top right base
        {-1.0f, 0.0f, -1.0f, .0f, .0f, 1.0f, .0f, .0f}, //bottom left base
        // 2/2 base
        { 1.0f, 0.0f, -1.0f, .0f, .0f, 1.0f, .0f, .0f}, //bottom right base
        {-1.0f, 0.0f, -1.0f, .0f, .0f, 1.0f, .0f, .0f}, //bottom left base
        { 1.0f, 0.0f,  1.0f, .0f, .0f, 1.0f, .0f, .0f}, //top right base
};

static const Vertex defaultEnemyModel [] = {
        // front face
        { 0.0f, 1.0f,  0.0f, 1.0f, .0f, .0f, .0f, .0f}, //tip
        {-1.0f, 0.0f,  1.0f, 1.0f, .0f, .0f, .0f, .0f}, //top left base
        { 1.0f, 0.0f,  1.0f, 1.0f, .0f, .0f, .0f, .0f}, //top right base
        // right face
        { 0.0f, 1.0f,  0.0f, 1.0f, .0f, .0f, .0f, .0f}, //tip
        { 1.0f, 0.0f,  1.0f, 1.0f, .0f, .0f, .0f, .0f}, //top right base
        { 1.0f, 0.0f, -1.0f, 1.0f, .0f, .0f, .0f, .0f}, //bottom right base
        // left face
        { 0.0f, 1.0f,  0.0f, 1.0f, .0f, .0f, .0f, .0f}, //tip
        {-1.0f, 0.0f, -1.0f, 1.0f, .0f, .0f, .0f, .0f}, //bottom left base
        {-1.0f, 0.0f,  1.0f, 1.0f, .0f, .0f, .0f, .0f}, //top left base
        // back face
        { 0.0f, 1.0f,  0.0f, 1.0f, .0f, .0f, .0f, .0f}, //tip
        { 1.0f, 0.0f, -1.0f, 1.0f, .0f, .0f, .0f, .0f}, //bottom right base
        {-1.0f, 0.0f, -1.0f, 1.0f, .0f, .0f, .0f, .0f}, //bottom left base
        // 1/2 base
        {-1.0f, 0.0f,  1.0f, 1.0f, .0f, .0f, .0f, .0f}, //top left base
        { 1.0f, 0.0f,  1.0f, 1.0f, .0f, .0f, .0f, .0f}, //top right base
        {-1.0f, 0.0f, -1.0f, 1.0f, .0f, .0f, .0f, .0f}, //bottom left base
        // 2/2 base
        { 1.0f, 0.0f, -1.0f, 1.0f, .0f, .0f, .0f, .0f}, //bottom right base
        {-1.0f, 0.0f, -1.0f, 1.0f, .0f, .0f, .0f, .0f}, //bottom left base
        { 1.0f, 0.0f,  1.0f, 1.0f, .0f, .0f, .0f, .0f}, //top right base
};
//static const Vertex defaultEnemyModel [] = {
//  {0.0f,    0.2f,  0.0f, 1.0f, 0.0f, 0.0f, 0.5f, 0.0f},
//  {-0.20f, -0.20f, 0.0f, 1.0f, 0.0f, 0.0f, 0.1f, 0.8f},
//  {0.20f,  -0.20f, 0.0f, 1.0f, 0.0f, 0.0f, 0.9f, 0.8f},
//};

Creature::Creature()
        :hp(0), attack(0), defense(0), speed(0)
{
}

Creature::Creature(float x, float y, float z, bool isEnemy=true)
        :hp(0), attack(0), defense(0), speed(1.0f), GameObject(x, y, z, 15)
{
    if (isEnemy){
        for (int i = 0; i < modelSize; i++) {
            modelVerts[i] = defaultPlayerModel[i];
            modelVerts[i].x += x;
            modelVerts[i].y += y;
            modelVerts[i].z += z;
        }
    }
    else {
        for (int i = 0; i < modelSize; i++) {
            modelVerts[i] = defaultEnemyModel[i];
            modelVerts[i].x += x;
            modelVerts[i].y += y;
            modelVerts[i].z += z;
        }
    }
}

Creature::Creature(float x, float y, float z, float scaleX, float scaleY, float scaleZ, bool isEnemy=true)
        :hp(0), attack(0), defense(0), speed(1.0f), GameObject(x, y, z, 15)
{
    if (isEnemy){
        for (int i = 0; i < modelSize; i++) {
            modelVerts[i] = defaultPlayerModel[i];
            modelVerts[i].x *= scaleX;
            modelVerts[i].y *= scaleY;
            modelVerts[i].z *= scaleZ;
            modelVerts[i].x += x;
            modelVerts[i].y += y;
            modelVerts[i].z += z;
        }
    }
    else {
        for (int i = 0; i < modelSize; i++) {
            modelVerts[i] = defaultEnemyModel[i];
            modelVerts[i].x *= scaleX;
            modelVerts[i].y *= scaleY;
            modelVerts[i].z *= scaleZ;
            modelVerts[i].x += x;
            modelVerts[i].y += y;
            modelVerts[i].z += z;
        }
    }
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
