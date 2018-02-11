//
// Created by leo on 2/10/18.
//

#include "GameObject.h"
#include <iostream>

GameObject::GameObject()
{
    std::cout << "DEFAULT OBJECT CONSTRUCTED" << std::endl;
}

GameObject::GameObject(Vertex* vertexData, int mSize) {
    modelSize = mSize;
    modelVerts = (Vertex*)malloc(mSize * sizeof(Vertex));
    for (int i = 0; i < mSize; i++) {
        modelVerts[i] = vertexData[i];
    }
}
