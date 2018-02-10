//
// Created by leo on 2/10/18.
//

#include "GameObject.h"

GameObject::GameObject(): modelVerts({
                             {-0.7f, -0.2f, 0.0f},
                             {-0.3f, -0.2f, 0.0f},
                             {-0.5f, 0.3f, 0.0f}})
{
}

GameObject::GameObject(Vertex* vertexData) {
    for (int i = 0; i < 3; i++) {
        modelVerts[i] = vertexData[i];
    }
}
