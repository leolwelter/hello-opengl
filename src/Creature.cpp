//
// Created by leo on 2/4/18.
//

#include "Creature.h"

static const Vertex defaultPlayerModel [] = {
        {0.0f,   -0.6f, 0.0f, 1.0f, 0.0f, 0.0f, 0.5f, 0.0f},
        {-0.20f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.1f, 0.8f},
        {0.20f,  -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.9f, 0.8f},
};

static const Vertex defaultEnemyModel [] = {
        {0.0f,   0.6f, 0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 0.0f},
        {-0.20f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.1f, 0.8f},
        {0.20f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.9f, 0.8f},
};

Creature::Creature()
        :hp(0), attack(0), defense(0), speed(0)
{
}

Creature::Creature(float x, float y, bool isEnemy=true)
        :hp(0), attack(0), defense(0), speed(0.015f), GameObject(x, y, 3)
{
    if (isEnemy){
        for (int i = 0; i < modelSize; i++) {
            modelVerts[i] = defaultPlayerModel[i];
            modelVerts[i].x += x;
            modelVerts[i].y += y;
        }
    }
    else {
        for (int i = 0; i < modelSize; i++) {
            modelVerts[i] = defaultEnemyModel[i];
            modelVerts[i].x += x;
            modelVerts[i].y += y;
        }
    }
}

Creature::Creature(Vertex* vertexData)
        :hp(0), attack(0), defense(0), speed(0), GameObject(vertexData, 3)
{
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
