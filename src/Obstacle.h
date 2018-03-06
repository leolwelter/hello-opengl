//
// Created by leo on 2/18/18.
//

#ifndef TEXTGAME_OBSTACLE_H
#define TEXTGAME_OBSTACLE_H


#include "GameObject.h"

class Obstacle: public GameObject {
public:
    Obstacle();
    Obstacle(float x, float y, float z);
    Obstacle(Vertex* vertexData);

private:

};


#endif //TEXTGAME_OBSTACLE_H
