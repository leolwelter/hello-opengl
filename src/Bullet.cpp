//
// Created by leo on 2/10/18.
//

#include "Bullet.h"


Bullet::Bullet(Vertex *vData, int side): GameObject(vData, 6) {
    if (side == PLAYER) {
        speed = 0.03f;
    }
    else if (side == ENEMY) {
        speed = -0.03f;
    }
}

void Bullet::fly() {
    for (int i = 0; i < modelSize; i++) {
        modelVerts[i].y += speed;
    }
}

