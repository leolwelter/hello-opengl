//
// Created by leo on 2/10/18.
//

#ifndef TEXTGAME_GAMEOBJECT_H
#define TEXTGAME_GAMEOBJECT_H


struct Vertex {
    float x;
    float y;
    float z;
};

class GameObject {
public:
    GameObject();
    GameObject(Vertex* vertexData);

    // graphic info
    unsigned int VBO;
    unsigned int VAO;
    Vertex modelVerts [3]; //model vertex data
};


#endif //TEXTGAME_GAMEOBJECT_H
