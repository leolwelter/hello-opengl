//
// Created by leo on 3/30/18.
//

#ifndef TEXTGAME_LIGHTSOURCE_H
#define TEXTGAME_LIGHTSOURCE_H


#include "GameObject.h"

static const Vertex defaultObstacleModel [] = {
        {-1.0f, -1.0f, -1.0f, .8f, .8f, .8f, 0.8f, 0.8f},
        { 1.0f, -1.0f, -1.0f, .8f, .8f, .8f, 1.8f, 0.8f},
        { 1.0f,  1.0f, -1.0f, .8f, .8f, .8f, 1.8f, 1.8f},
        { 1.0f,  1.0f, -1.0f, .8f, .8f, .8f, 1.8f, 1.8f},
        {-1.0f,  1.0f, -1.0f, .8f, .8f, .8f, 0.8f, 1.8f},
        {-1.0f, -1.0f, -1.0f, .8f, .8f, .8f, 0.8f, 0.8f},

        {-1.0f, -1.0f,  1.0f, .8f, .8f, .8f, 0.8f, 0.8f},
        { 1.0f, -1.0f,  1.0f, .8f, .8f, .8f, 1.8f, 0.8f},
        { 1.0f,  1.0f,  1.0f, .8f, .8f, .8f, 1.8f, 1.8f},
        { 1.0f,  1.0f,  1.0f, .8f, .8f, .8f, 1.8f, 1.8f},
        {-1.0f,  1.0f,  1.0f, .8f, .8f, .8f, 0.8f, 1.8f},
        {-1.0f, -1.0f,  1.0f, .8f, .8f, .8f, 0.8f, 0.8f},

        {-1.0f,  1.0f,  1.0f, .8f, .8f, .8f, 1.8f, 0.8f},
        {-1.0f,  1.0f, -1.0f, .8f, .8f, .8f, 1.8f, 1.8f},
        {-1.0f, -1.0f, -1.0f, .8f, .8f, .8f, 0.8f, 1.8f},
        {-1.0f, -1.0f, -1.0f, .8f, .8f, .8f, 0.8f, 1.8f},
        {-1.0f, -1.0f,  1.0f, .8f, .8f, .8f, 0.8f, 0.8f},
        {-1.0f,  1.0f,  1.0f, .8f, .8f, .8f, 1.8f, 0.8f},

        {1.0f,  1.0f,  1.0f, .8f, .8f, .8f, 1.8f, 0.8f},
        {1.0f,  1.0f, -1.0f, .8f, .8f, .8f, 1.8f, 1.8f},
        {1.0f, -1.0f, -1.0f, .8f, .8f, .8f, 0.8f, 1.8f},
        {1.0f, -1.0f, -1.0f, .8f, .8f, .8f, 0.8f, 1.8f},
        {1.0f, -1.0f,  1.0f, .8f, .8f, .8f, 0.8f, 0.8f},
        {1.0f,  1.0f,  1.0f, .8f, .8f, .8f, 1.8f, 0.8f},

        {-1.0f, -1.0f, -1.0f, .8f, .8f, .8f, 0.8f, 1.8f},
        { 1.0f, -1.0f, -1.0f, .8f, .8f, .8f, 1.8f, 1.8f},
        { 1.0f, -1.0f,  1.0f, .8f, .8f, .8f, 1.8f, 0.8f},
        { 1.0f, -1.0f,  1.0f, .8f, .8f, .8f, 1.8f, 0.8f},
        {-1.0f, -1.0f,  1.0f, .8f, .8f, .8f, 0.8f, 0.8f},
        {-1.0f, -1.0f, -1.0f, .8f, .8f, .8f, 0.8f, 1.8f},

        {-1.0f,  1.0f, -1.0f, .8f, .8f, .8f, 0.8f, 1.8f},
        { 1.0f,  1.0f, -1.0f, .8f, .8f, .8f, 1.8f, 1.8f},
        { 1.0f,  1.0f,  1.0f, .8f, .8f, .8f, 1.8f, 0.8f},
        { 1.0f,  1.0f,  1.0f, .8f, .8f, .8f, 1.8f, 0.8f},
        {-1.0f,  1.0f,  1.0f, .8f, .8f, .8f, 0.8f, 0.8f},
        {-1.0f,  1.0f, -1.0f, .8f, .8f, .8f, 0.8f, 1.8f}
};

class LightSource: public GameObject{
public:
    // constructors
    LightSource() {}
    LightSource(float x, float y, float z)
        :GameObject(x, y, z, 36){
        color = glm::vec3(.9f, .9f, .4f);
        for (int i = 0; i < modelSize; i++) {
            modelVerts[i] = defaultObstacleModel[i];
            modelVerts[i].x += x;
            modelVerts[i].y += y;
            modelVerts[i].z += z;
            modelVerts[i].red = color.r;
            modelVerts[i].green = color.g;
            modelVerts[i].blue = color.b;
        }
    }

    glm::vec3 color;

};


#endif //TEXTGAME_LIGHTSOURCE_H
