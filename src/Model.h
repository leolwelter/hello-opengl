//
// Created by leo on 4/19/18.
//

#ifndef TEXTGAME_MODEL_H
#define TEXTGAME_MODEL_H


#include <vector>
#include "Shader.h"
#include "Mesh.h"

class Model {
public:
    Model(char* path) {
        loadModel(path);
    }

    Model() {}

    void draw(Shader shader) {
        for (int i = 0; i < meshes.size(); i++)
            meshes[i].draw(shader);
    }

private:
    std::vector<Mesh> meshes;
    std::string dir;

    void loadModel(std::string path) {
        Assimp::Importer importer;
        const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            std::cout << importer.GetErrorString() << std::endl;
        }
        dir = path.substr(0, path.find_last_of("/"));
        processNode(scene->mRootNode, scene);
    };

    void processNode(aiNode *node, const aiScene *scene) {
        // first load all meshes for the given node
        for (unsigned int i = 0; i < node->mNumMeshes; i++) {
            aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
            meshes.push_back(processMesh(mesh, scene));
        }

        // breadth-first recursion for all nodes
        for (unsigned int i = 0; i < node->mNumChildren; i++) {
            processNode(node->mChildren[i], scene);
        }
    };

    Mesh processMesh(aiMesh *mesh, const aiScene *scene) {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;

        // retrieve vertex data
        for (unsigned int i = 0; i < mesh->mNumVertices; i++){
            Vertex v;
            v.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
            v.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);

            // retrieve texture coordinates (if any)
            if(mesh->mTextureCoords[0]) {
                v.texCoords = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
            }
            else {
                v.texCoords = glm::vec2(0.0f);
            }
            vertices.push_back(v);
        }

        // retrieve indices
        for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
            aiFace f = mesh->mFaces[i];
            for (unsigned int j = 0; j < f.mNumIndices; j++)
                indices.push_back(f.mIndices[j]);
        }

        // retrieve material properties
        if (mesh->mMaterialIndex >= 0) {
            aiMaterial *mat = scene->mMaterials[mesh->mMaterialIndex];
            std::vector<Texture> diffuseMaps = loadMaterialTextures(mat, aiTextureType_DIFFUSE, "texture_diffuse");
            textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

            std::vector<Texture> specularMaps = loadMaterialTextures(mat, aiTextureType_SPECULAR, "texture_specular");
            textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        }

        return Mesh(vertices, indices, textures);
    };

    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName) {
        std::vector<Texture> texts;
        for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
            unsigned int j = mat->GetTextureCount(type);
            aiString str;
            mat->GetTexture(type, i, &str);
            Texture tex;

            // strip double backslash from paths
            std::string checkStr = str.C_Str();
            std::string dbSlash = "\\";
            if (checkStr.find(dbSlash) != std::string::npos) {
                checkStr.replace(checkStr.find(dbSlash), dbSlash.length(), "/");
                str.Set(checkStr);
            }

            tex.id = textureFromFile(str.C_Str(), dir, false);
            tex.type = typeName;
            tex.path = str.C_Str();
            texts.push_back(tex);
        }
        return texts;
    };

    unsigned int textureFromFile(const char *path, const std::string &directory, bool gamma)
    {
        std::string filename = std::string(path);
        filename = directory + '/' + filename;

        unsigned int textureID;
        glGenTextures(1, &textureID);

        int width, height, nrComponents;
        unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
        if (data)
        {
            GLenum format;
            if (nrComponents == 1)
                format = GL_RED;
            else if (nrComponents == 3)
                format = GL_RGB;
            else if (nrComponents == 4)
                format = GL_RGBA;

            glBindTexture(GL_TEXTURE_2D, textureID);
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            stbi_image_free(data);
        }
        else
        {
            std::cout << "Texture failed to load at path: " << path << std::endl;
            stbi_image_free(data);
        }

        return textureID;
    }
};


#endif //TEXTGAME_MODEL_H
