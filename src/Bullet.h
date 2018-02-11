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
    Bullet(Vertex* vData, int side);

    // game actions
    void fly();
private:
    float speed;
};


#endif //TEXTGAME_BULLET_H
