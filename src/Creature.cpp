//
// Created by leo on 2/4/18.
//

#include <iostream>
#include <cstring>
#include "Creature.h"

Creature::Creature()
        :hp(0), attack(0), defense(0), speed(0),
         modelVerts{
                 {-0.7f, -0.2f, 0.0f},
                 {-0.3f, -0.2f, 0.0f},
                 {-0.5f, 0.3f, 0.0f}}
{
}

Creature::Creature(Vertex* vertexData):hp(0), attack(0), defense(0), speed(0) {
    for (int i = 0; i < 3; i++) {
        modelVerts[i] = vertexData[i];
    }
}

void Creature::move(float dx, float dy, float dz) {
    // apply dx/y/z to each vertex of the model
    for (auto &modelVert : modelVerts) {
        modelVert.x += dx;
        modelVert.y += dy;
        modelVert.z += dz;
    }
}

void Creature::displayInfo() {
    std::cout << "HP: " << hp << std::endl;
    std::cout << "ATTK: " << attack << std::endl;
    std::cout << "DEF: " << defense << std::endl;
    std::cout << "SPD: " << speed << std::endl;
}

void Creature::move(int direction) {
    switch (direction) {
        case UP:
            move(.0f, 0.03f, .0f);
            break;
        case DOWN:
            move(.0f, -0.03f, .0f);
            break;
        case LEFT:
            move(-0.03f, .0f, .0f);
            break;
        case RIGHT:
            move(0.03f, .0f, .0f);
            break;
        default:
            std::cout << "STAYING STILL" << std::endl;
            break;
    }
}