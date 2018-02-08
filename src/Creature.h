//
// Created by leo on 2/4/18.
//

#ifndef TEXTGAME_CREATURE_H
#define TEXTGAME_CREATURE_H

struct Vertex {
    float x;
    float y;
    float z;
};

enum DIRECTION {
    UP, LEFT, DOWN, RIGHT
};

class Creature {
public:
    // constructors
    Creature();
    Creature(Vertex* vertexData);

    // stat accessors
    void setHP(int hp_t) { hp = hp_t; };
    void setAttack(int attack_t) { attack = attack_t; };
    void setDefense(int defense_t) { defense = defense_t; };
    void setSpeed(int speed_t) { speed = speed_t; };

    int getHP() { return hp; };
    int getAttack() { return attack; };
    int getDefense() { return defense; };
    int getSpeed() { return speed; };
    void displayInfo();

    // game actions
    void move(float dx, float dy, float dz);
    void move(int direction);
    int direction;

    // graphic info
    unsigned int VBO;
    unsigned int VAO;
    Vertex modelVerts [3]; //model vertex data


private:
    int hp;
    int attack;
    int defense;
    int speed;
};


#endif //TEXTGAME_CREATURE_H
