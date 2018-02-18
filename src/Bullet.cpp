//
// Created by leo on 2/10/18.
//

#include "Bullet.h"


Bullet::Bullet(Vertex *vData, int side, int vHorizontal): GameObject(vData, 6) {
    if (side == PLAYER) {
        speedY = 0.03f;
    }
    else if (side == ENEMY) {
        speedY = -0.03f;
    }

    if (vHorizontal == RIGHT) {
        speedX = 0.01f;
    }
    else if (vHorizontal == LEFT) {
        speedX = -0.01f;
    }
    else {
        speedX = 0.0f;
    }
}

void Bullet::fly() {
    for (int i = 0; i < modelSize; i++) {
        modelVerts[i].y += speedY;
        modelVerts[i].x += speedX;
    }
}

