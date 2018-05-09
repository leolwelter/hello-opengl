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
    Creature(glm::vec3 position, glm::vec3 scale, char* modelPath)
            :hp(1.0f), attack(1.0f), defense(1.0f), speed(3.0f), GameObject(position, scale, modelPath)
    {}

    void setHP(int hp_t) { hp = hp_t; };
    void setAttack(int attack_t) { attack = attack_t; };
    void setDefense(int defense_t) { defense = defense_t; };
    void setSpeed(int speed_t) { speed = speed_t; };

    int getHP() { return hp; };
    int getAttack() { return attack; };
    int getDefense() { return defense; };
    float getSpeed() { return speed; };
    void printPos() {
        std::cout << "[" << position.x << ", " << position.y << ", " << position.z << "]" << std::endl;
    }
    void printFacing() {
        std::cout << "Facing <" << modelFront.x << ", " << modelFront.y << ", " << modelFront.z << ">" << std::endl;
    }
private:
    float hp;
    float attack;
    float defense;
    float speed;
};


#endif //TEXTGAME_CREATURE_H
