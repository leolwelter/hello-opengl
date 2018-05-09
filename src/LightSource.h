//
// Created by leo on 3/30/18.
//

#ifndef TEXTGAME_LIGHTSOURCE_H
#define TEXTGAME_LIGHTSOURCE_H


#include "GameObject.h"

#define DAY_IN_SECONDS 24
#define STD_CONST_ATTEN 1.0f
#define STD_LIN_ATTEN 0.07f
#define STD_QUAD_ATTEN 0.017f

static const glm::vec3 LIGHTSOURCE_STD_INTENSITY = glm::vec3(0.2f, 3.0f, 1.0f);
static const glm::vec3 LIGHTSOURCE_LOW_INTENSITY = glm::vec3(0.2f, 1.0f, 1.0f);
static const glm::vec3 LIGHTSOURCE_HIGH_INTENSITY = glm::vec3(0.2f, 6.0f, 1.0f);


struct LightIntensity {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

class LightSource: public GameObject{
public:
    // constructors
    LightSource(glm::vec3 position, glm::vec3 scale, char* modelPath, glm::vec3 intensities, glm::vec3 vColor, char axis)
            :GameObject(position, scale, modelPath) ,rotAxis(axis)
    {
        lIntensity = {intensities.x * vColor, intensities.y * vColor, intensities.z * vColor};
        lDirection = glm::vec3(0.0f, -1.0f, 0.0f);
        attenConstant = STD_CONST_ATTEN;
        attenLinear = STD_LIN_ATTEN;
        attenQuad = STD_QUAD_ATTEN;
        cutoffAngle = 30.0f;
        cutoffOuter = 33.0f;
        color = vColor;
        speed = 25.0f;
    }

    // methods
    void setIntensity(glm::vec3 intensities) {
        lIntensity = {intensities.x * color, intensities.y * color, intensities.z * color};
    }

    void orbit(float deltaT) {
        if (rotAxis == 'X')
            orbitX(deltaT);
        else if (rotAxis == 'Y')
            orbitY(deltaT);
        else if (rotAxis == 'Z')
            orbitZ(deltaT);
    }

    void orbitZ(float deltaT) {
        float tmpX = position.x * cos(deltaT * speed / DAY_IN_SECONDS) - position.y * sin(deltaT * speed / DAY_IN_SECONDS);
        float tmpY = position.y * cos(deltaT * speed / DAY_IN_SECONDS) + position.x * sin(deltaT * speed / DAY_IN_SECONDS);
        position.x = tmpX;
        position.y = tmpY;
    }

    void orbitX(float deltaT) {
        float tmpY = position.y * cos(deltaT * speed / DAY_IN_SECONDS) - position.z * sin(deltaT * speed / DAY_IN_SECONDS);
        float tmpZ = position.z * cos(deltaT * speed / DAY_IN_SECONDS) + position.y * sin(deltaT * speed / DAY_IN_SECONDS);
        position.y = tmpY;
        position.z = tmpZ;
    }

    void orbitY(float deltaT) {
        float tmpX = position.x * cos(deltaT * speed / DAY_IN_SECONDS) - position.z * sin(deltaT * speed / DAY_IN_SECONDS);
        float tmpZ = position.z * cos(deltaT * speed / DAY_IN_SECONDS) + position.x * sin(deltaT * speed / DAY_IN_SECONDS);
        position.x = tmpX;
        position.z = tmpZ;
    }

    // attributes
    glm::vec3 color;
    LightIntensity lIntensity;
    glm::vec3 lDirection;   // for directional and spot lights
    float cutoffAngle{};      // for spot lights
    float cutoffOuter{};      // for spot lights
    char rotAxis;
    float speed;
    float attenConstant;
    float attenLinear;
    float attenQuad;
};


#endif //TEXTGAME_LIGHTSOURCE_H
