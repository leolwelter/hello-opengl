//
// Created by leo on 2/10/18.
//

#include "Bullet.h"


void Bullet::fly() {
    for (int i = 0; i < modelSize; i++) {
        modelVerts[i].y += speedY;
        modelVerts[i].x += speedX;
    }
}

