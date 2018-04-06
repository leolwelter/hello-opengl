//
// Created by leo on 3/30/18.
//

#ifndef TEXTGAME_LIGHTSOURCE_H
#define TEXTGAME_LIGHTSOURCE_H


#include "GameObject.h"

#define DAY_IN_SECONDS 10

static const Vertex defaultObstacleModel [] = {
        {-1.0f, -1.0f, -1.0f, .0f, .0f, .0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f},
        { 1.0f, -1.0f, -1.0f, .0f, .0f, .0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f},
        { 1.0f,  1.0f, -1.0f, .0f, .0f, .0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f},
        { 1.0f,  1.0f, -1.0f, .0f, .0f, .0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f},
        {-1.0f,  1.0f, -1.0f, .0f, .0f, .0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f},
        {-1.0f, -1.0f, -1.0f, .0f, .0f, .0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f},

        {-1.0f, -1.0f,  1.0f, .0f, .0f, .0f, 0.0f, 0.0f, 0.0f, 0.0f,  1.0f},
        { 1.0f, -1.0f,  1.0f, .0f, .0f, .0f, 1.0f, 0.0f, 0.0f, 0.0f,  1.0f},
        { 1.0f,  1.0f,  1.0f, .0f, .0f, .0f, 1.0f, 1.0f, 0.0f, 0.0f,  1.0f},
        { 1.0f,  1.0f,  1.0f, .0f, .0f, .0f, 1.0f, 1.0f, 0.0f, 0.0f,  1.0f},
        {-1.0f,  1.0f,  1.0f, .0f, .0f, .0f, 0.0f, 1.0f, 0.0f, 0.0f,  1.0f},
        {-1.0f, -1.0f,  1.0f, .0f, .0f, .0f, 0.0f, 0.0f, 0.0f, 0.0f,  1.0f},

        {-1.0f,  1.0f,  1.0f, .0f, .0f, .0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f},
        {-1.0f,  1.0f, -1.0f, .0f, .0f, .0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f},
        {-1.0f, -1.0f, -1.0f, .0f, .0f, .0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f},
        {-1.0f, -1.0f, -1.0f, .0f, .0f, .0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f},
        {-1.0f, -1.0f,  1.0f, .0f, .0f, .0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f},
        {-1.0f,  1.0f,  1.0f, .0f, .0f, .0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f},

        {1.0f,  1.0f,  1.0f, .0f, .0f, .0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f},
        {1.0f,  1.0f, -1.0f, .0f, .0f, .0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f},
        {1.0f, -1.0f, -1.0f, .0f, .0f, .0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f},
        {1.0f, -1.0f, -1.0f, .0f, .0f, .0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f},
        {1.0f, -1.0f,  1.0f, .0f, .0f, .0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
        {1.0f,  1.0f,  1.0f, .0f, .0f, .0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f},

        {-1.0f, -1.0f, -1.0f, .0f, .0f, .0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f},
        { 1.0f, -1.0f, -1.0f, .0f, .0f, .0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f},
        { 1.0f, -1.0f,  1.0f, .0f, .0f, .0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f},
        { 1.0f, -1.0f,  1.0f, .0f, .0f, .0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f},
        {-1.0f, -1.0f,  1.0f, .0f, .0f, .0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f},
        {-1.0f, -1.0f, -1.0f, .0f, .0f, .0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f},

        {-1.0f,  1.0f, -1.0f, .0f, .0f, .0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f},
        { 1.0f,  1.0f, -1.0f, .0f, .0f, .0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f},
        { 1.0f,  1.0f,  1.0f, .0f, .0f, .0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f},
        { 1.0f,  1.0f,  1.0f, .0f, .0f, .0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f},
        {-1.0f,  1.0f,  1.0f, .0f, .0f, .0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f},
        {-1.0f,  1.0f, -1.0f, .0f, .0f, .0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f}
};

class LightSource: public GameObject{
public:
    // constructors
    LightSource() {}
    LightSource(float x, float y, float z, glm::vec3 vColor)
        :GameObject(x, y, z, 36){
        for (int i = 0; i < modelSize; i++) {
            modelVerts[i] = defaultObstacleModel[i];
            modelVerts[i].red = vColor.r;
            modelVerts[i].green = vColor.g;
            modelVerts[i].blue = vColor.b;
        }
        coordX = x;
        coordY = y;
        coordZ = z;
        color = vColor;
    }

    // methods
    void orbit(float deltaT) {
        float tmpX = coordX * cos(deltaT / DAY_IN_SECONDS) - coordY * sin(deltaT / DAY_IN_SECONDS);
        float tmpY = coordY * cos(deltaT / DAY_IN_SECONDS) + coordX * sin(deltaT / DAY_IN_SECONDS);
        coordX = tmpX;
        coordY = tmpY;
    }

    // attributes
    glm::vec3 color;


};


#endif //TEXTGAME_LIGHTSOURCE_H
