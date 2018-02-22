//
// Created by leo on 2/4/18.
//

#include "Creature.h"

static const Vertex defaultPlayerModel [] = {
        {0.0f,   -0.6f, 0.0f, 1.0f, 0.0f, 0.0f, 0.5f, 1.0f},
        {-0.20f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f},
        {0.20f,  -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f},
};

static const Vertex defaultEnemyModel [] = {
        {0.0f,   0.6f, 0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 0.0f},
        {-0.20f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f},
        {0.20f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f},
};

Creature::Creature()
        :hp(0), attack(0), defense(0), speed(0)
{
}

Creature::Creature(float x, float y, bool isEnemy=true)
        :hp(0), attack(0), defense(0), speed(0), GameObject(x, y, 3)
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

void Creature::move(float dx, float dy, float dz) {
    // apply dx/y/z to each vertex of the model
    for (int i = 0; i < modelSize; i++) {
        modelVerts[i].x += dx;
        modelVerts[i].y += dy;
        modelVerts[i].z += dz;
    }
}


void Creature::move(int direction) {
    switch (direction) {
        case UP:
            move(.0f, 0.02f, .0f);
            break;
        case DOWN:
            move(.0f, -0.02f, .0f);
            break;
        case LEFT:
            move(-0.02f, .0f, .0f);
            break;
        case RIGHT:
            move(0.02f, .0f, .0f);
            break;
        default:
            std::cout << "STAYING STILL" << std::endl;
            break;
    }
}
