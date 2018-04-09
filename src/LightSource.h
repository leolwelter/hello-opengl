//
// Created by leo on 3/30/18.
//

#ifndef TEXTGAME_LIGHTSOURCE_H
#define TEXTGAME_LIGHTSOURCE_H


#include "GameObject.h"

#define DAY_IN_SECONDS 24

struct ShaderLightStruct {
    glm::vec3 position;
    glm::vec3 color;
};

struct LightIntensity {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

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
        rotAxis = 'X';
        speed = 1.0f;
        lIntensity = {0.2f * vColor, 0.5f * vColor, 1.0f * vColor};
        generateVertexObjects();
    }

    LightSource(float x, float y, float z, glm::vec3 vColor, glm::vec3 pscale, char axis, float speed)
            :GameObject(x, y, z, 36), rotAxis(axis), speed(speed) {
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
        scale = pscale;
        lIntensity = {0.2f * vColor, 0.5f * vColor, 1.0f * vColor};
        generateVertexObjects();
    }

    LightSource(float x, float y, float z, glm::vec3 vColor, glm::vec3 intensities, glm::vec3 pscale, char axis, float speed)
            :GameObject(x, y, z, 36), rotAxis(axis), speed(speed) {
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
        scale = pscale;
        lIntensity = {intensities.x * vColor, intensities.y * vColor, intensities.z * vColor};
        generateVertexObjects();
    }

    // methods
    void orbit(float deltaT) {
        if (rotAxis == 'X')
            orbitX(deltaT);
        else if (rotAxis == 'Y')
            orbitY(deltaT);
        else if (rotAxis == 'Z')
            orbitZ(deltaT);
    }

    void orbitZ(float deltaT) {
        float tmpX = coordX * cos(deltaT * speed / DAY_IN_SECONDS) - coordY * sin(deltaT * speed / DAY_IN_SECONDS);
        float tmpY = coordY * cos(deltaT * speed / DAY_IN_SECONDS) + coordX * sin(deltaT * speed / DAY_IN_SECONDS);
        coordX = tmpX;
        coordY = tmpY;
    }

    void orbitX(float deltaT) {
        float tmpY = coordY * cos(deltaT * speed / DAY_IN_SECONDS) - coordZ * sin(deltaT * speed / DAY_IN_SECONDS);
        float tmpZ = coordZ * cos(deltaT * speed / DAY_IN_SECONDS) + coordY * sin(deltaT * speed / DAY_IN_SECONDS);
        coordY = tmpY;
        coordZ = tmpZ;
    }

    void orbitY(float deltaT) {
        float tmpX = coordX * cos(deltaT * speed / DAY_IN_SECONDS) - coordZ * sin(deltaT * speed / DAY_IN_SECONDS);
        float tmpZ = coordZ * cos(deltaT * speed / DAY_IN_SECONDS) + coordX * sin(deltaT * speed / DAY_IN_SECONDS);
        coordX = tmpX;
        coordZ = tmpZ;
    }

    ShaderLightStruct getShaderLightStruct() {
        ShaderLightStruct tmp;
        tmp.position = getPos();
        tmp.color = color;
        return tmp;
    }

    // attributes
    glm::vec3 color;
    LightIntensity lIntensity;
    char rotAxis;
    float speed;
};


#endif //TEXTGAME_LIGHTSOURCE_H
