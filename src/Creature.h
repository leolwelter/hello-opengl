//
// Created by leo on 2/4/18.
//

#ifndef TEXTGAME_CREATURE_H
#define TEXTGAME_CREATURE_H

#include "GameObject.h"
#include <iostream>





class Creature: public GameObject {
public:
    // constructors
    Creature();
    Creature(float x, float y, float z, bool isEnemy);
    Creature(Vertex* vertexData);

    // stat accessors
    void setHP(int hp_t) { hp = hp_t; };
    void setAttack(int attack_t) { attack = attack_t; };
    void setDefense(int defense_t) { defense = defense_t; };
    void setSpeed(int speed_t) { speed = speed_t; };

    int getHP() { return hp; };
    int getAttack() { return attack; };
    int getDefense() { return defense; };
    float getSpeed() { return speed; };

    // game actions
    glm::mat4 move(float dx, float dy, float dz);
    glm::mat4 move(int direction);
    int direction;


private:
    int hp;
    int attack;
    int defense;
    float speed;
};


#endif //TEXTGAME_CREATURE_H
