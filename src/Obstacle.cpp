//
// Created by leo on 2/18/18.
//

#include "Obstacle.h"

static const Vertex defaultObstacleModel [] = {
        {-.2f, -.2f,  0.0f, 1.0f, 0.0f, 0.0f,  0.0f,  0.0f},
        {.2f,   .2f,  0.0f, 0.0f, 1.0f, 0.0f,  1.0f,  1.0f},
        {-.2f,  .2f,  0.0f, 0.0f, 0.0f, 1.0f,  0.0f,  1.0f},
        {-.2f, -.2f,  0.0f, 1.0f, 0.0f, 0.0f,  0.0f,  0.0f},
        {.2f,   .2f,  0.0f, 0.0f, 1.0f, 0.0f,  1.0f,  1.0f},
        {.2f,  -.2f,  0.0f, 0.0f, 0.0f, 1.0f,  1.0f,  0.0f},
};

Obstacle::Obstacle()
{
}


Obstacle::Obstacle(float x, float y)
    :GameObject(x, y, 6)
{
    for (int i = 0; i < modelSize; i++) {
        modelVerts[i] = defaultObstacleModel[i];
        modelVerts[i].x += x;
        modelVerts[i].y += y;
    }
}


Obstacle::Obstacle(Vertex *vertexData)
    :GameObject(vertexData, 6)
{
}