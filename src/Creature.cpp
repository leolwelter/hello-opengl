//
// Created by leo on 2/4/18.
//

#include <iostream>
#include <cstring>
#include "Creature.h"

Creature::Creature() :hp(0), attack(0), defense(0), speed(0)
{
}

Creature::Creature(Vertex* vertexData):hp(0), attack(0), defense(0), speed(0), GameObject(vertexData, 3) {
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
