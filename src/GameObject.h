//
// Created by leo on 2/10/18.
//

#ifndef TEXTGAME_GAMEOBJECT_H
#define TEXTGAME_GAMEOBJECT_H

enum DIRECTION {
    UP, LEFT, DOWN, RIGHT
};

struct Vertex {
    float x, y, z;
    float red, green, blue;
};

class GameObject {
public:
    GameObject();
    GameObject(Vertex* vertexData, int mSize);

    // graphic info
    unsigned int VBO;
    unsigned int VAO;
    Vertex* modelVerts; //model vertex data
    int modelSize;
};


#endif //TEXTGAME_GAMEOBJECT_H
