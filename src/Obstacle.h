//
// Created by leo on 2/18/18.
//

#ifndef TEXTGAME_OBSTACLE_H
#define TEXTGAME_OBSTACLE_H


#include "GameObject.h"

class Obstacle: public GameObject {
public:
    Obstacle(glm::vec3 position, glm::vec3 scale, Material material, char* modelpath)
            :GameObject(position, scale, modelpath)
    {}
};


#endif //TEXTGAME_OBSTACLE_H
