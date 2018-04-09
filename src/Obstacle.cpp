//
// Created by leo on 2/18/18.
//

#include "Obstacle.h"

static const Vertex defaultObstacleModel [] = {
        // coordinates        // colors      // textures // normal vectors
        {-0.2f, -0.2f, -0.2f, .0f, .0f, .0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f},
        { 0.2f, -0.2f, -0.2f, .0f, .0f, .0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f},
        { 0.2f,  0.2f, -0.2f, .0f, .0f, .0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f},
        { 0.2f,  0.2f, -0.2f, .0f, .0f, .0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f},
        {-0.2f,  0.2f, -0.2f, .0f, .0f, .0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f},
        {-0.2f, -0.2f, -0.2f, .0f, .0f, .0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f},

        {-0.2f, -0.2f,  0.2f, .0f, .0f, .0f, 0.0f, 0.0f, 0.0f, 0.0f,  1.0f},
        { 0.2f, -0.2f,  0.2f, .0f, .0f, .0f, 1.0f, 0.0f, 0.0f, 0.0f,  1.0f},
        { 0.2f,  0.2f,  0.2f, .0f, .0f, .0f, 1.0f, 1.0f, 0.0f, 0.0f,  1.0f},
        { 0.2f,  0.2f,  0.2f, .0f, .0f, .0f, 1.0f, 1.0f, 0.0f, 0.0f,  1.0f},
        {-0.2f,  0.2f,  0.2f, .0f, .0f, .0f, 0.0f, 1.0f, 0.0f, 0.0f,  1.0f},
        {-0.2f, -0.2f,  0.2f, .0f, .0f, .0f, 0.0f, 0.0f, 0.0f, 0.0f,  1.0f},

        {-0.2f,  0.2f,  0.2f, .0f, .0f, .0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f},
        {-0.2f,  0.2f, -0.2f, .0f, .0f, .0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f},
        {-0.2f, -0.2f, -0.2f, .0f, .0f, .0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f},
        {-0.2f, -0.2f, -0.2f, .0f, .0f, .0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f},
        {-0.2f, -0.2f,  0.2f, .0f, .0f, .0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f},
        {-0.2f,  0.2f,  0.2f, .0f, .0f, .0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f},

        {0.2f,  0.2f,  0.2f, .0f, .0f, .0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f},
        {0.2f,  0.2f, -0.2f, .0f, .0f, .0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f},
        {0.2f, -0.2f, -0.2f, .0f, .0f, .0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f},
        {0.2f, -0.2f, -0.2f, .0f, .0f, .0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f},
        {0.2f, -0.2f,  0.2f, .0f, .0f, .0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
        {0.2f,  0.2f,  0.2f, .0f, .0f, .0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f},

        {-0.2f, -0.2f, -0.2f, .0f, .0f, .0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f},
        { 0.2f, -0.2f, -0.2f, .0f, .0f, .0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f},
        { 0.2f, -0.2f,  0.2f, .0f, .0f, .0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f},
        { 0.2f, -0.2f,  0.2f, .0f, .0f, .0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f},
        {-0.2f, -0.2f,  0.2f, .0f, .0f, .0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f},
        {-0.2f, -0.2f, -0.2f, .0f, .0f, .0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f},

        {-0.2f,  0.2f, -0.2f, .0f, .0f, .0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f},
        { 0.2f,  0.2f, -0.2f, .0f, .0f, .0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f},
        { 0.2f,  0.2f,  0.2f, .0f, .0f, .0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f},
        { 0.2f,  0.2f,  0.2f, .0f, .0f, .0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f},
        {-0.2f,  0.2f,  0.2f, .0f, .0f, .0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f},
        {-0.2f,  0.2f, -0.2f, .0f, .0f, .0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f}
};

Obstacle::Obstacle()
{
}


Obstacle::Obstacle(float x, float y, float z)
    :GameObject(x, y, z, 36)
{
    for (int i = 0; i < modelSize; i++) {
        modelVerts[i] = defaultObstacleModel[i];
    }
    coordX = x;
    coordY = y;
    coordZ = z;
    scale = glm::vec3(1.0f, 1.0f, 1.0f);
    generateVertexObjects();
}


Obstacle::Obstacle(float x, float y, float z, float scaleX, float scaleY, float scaleZ)
        :GameObject(x, y, z, 36)
{
    for (int i = 0; i < modelSize; i++) {
        modelVerts[i] = defaultObstacleModel[i];
    }
    coordX = x;
    coordY = y;
    coordZ = z;
    scale = glm::vec3(scaleX, scaleY, scaleZ);
    generateVertexObjects();
}