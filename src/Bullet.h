//
// Created by leo on 2/10/18.
//

#ifndef TEXTGAME_BULLET_H
#define TEXTGAME_BULLET_H


#include "GameObject.h"

enum SIDE {
    PLAYER,
    ENEMY
};


class Bullet: public GameObject {
public:
    Bullet(Vertex* vData, int side, int vHor);

    // game actions
    void fly();
private:
    float speedY;
    float speedX;
};


#endif //TEXTGAME_BULLET_H
