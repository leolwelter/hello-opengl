//
// Created by leo on 2/17/18.
//

#ifndef TEXTGAME_SHADER_H
#define TEXTGAME_SHADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <glad/glad.h>

class Shader {
public:
    // constructors
    Shader():programID(0) {
        std::cout << "Default Shader" << std::endl;
    }

    Shader(const char* vertexPath, const char* fragmentPath) {
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;

        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        // use file streams to extract shader source(s)
        try {
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);

            std::stringstream vShaderStream,fShaderStream;

            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();

            vShaderFile.close();
            fShaderFile.close();

            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure ex) {
            std::cout << "ERROR Reading shader files" << std::endl;
        }

        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();

        // compile shader sources
        unsigned int vertex, fragment;
        int compSuccess;
        char log[512];

        // vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);

        glGetShaderiv(vertex, GL_COMPILE_STATUS, &compSuccess);
        if (!compSuccess) {
            glGetShaderInfoLog(vertex, 512, NULL, log);
            std::cout << "ERROR COMPILING VERTEX SHADER\n" << log << std::endl;
        }

        // fragment shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);

        glGetShaderiv(fragment, GL_COMPILE_STATUS, &compSuccess);
        if (!compSuccess) {
            glGetShaderInfoLog(fragment, 512, NULL, log);
            std::cout << "ERROR COMPILING FRAGMENT SHADER\n" << log << std::endl;
        }

        // link shader program
        programID = glCreateProgram();
        glAttachShader(programID, vertex);
        glAttachShader(programID, fragment);
        glLinkProgram(programID);

        glGetProgramiv(programID, GL_LINK_STATUS, &compSuccess);
        if (!compSuccess) {
            glGetProgramInfoLog(programID, 512, NULL, log);
            std::cout << "ERROR LINKING SHADER PROGRAM\n" << log << std::endl;
        }

        glDeleteShader(vertex);
        glDeleteShader(fragment);
    };

    void use() {
        glUseProgram(programID);
    };

    void setBool(const std::string &name, bool val) const {
        glUniform1i(glGetUniformLocation(programID, name.c_str()), (int)val);
    };

    void setInt(const std::string &name, int val) const {
        glUniform1i(glGetUniformLocation(programID, name.c_str()), val);
    };

    void setFloat(const std::string &name, float val) const {
        glUniform1f(glGetUniformLocation(programID, name.c_str()), val);
    };

    void setMat4(const std::string &name, glm::mat4 &mat) const {
        unsigned int loc = glGetUniformLocation(programID, name.c_str());
        glUniformMatrix4fv(loc, 1, GL_FALSE, &mat[0][0]);
    };
    void setVec3(const std::string &name, glm::vec3 &vec) const {
        unsigned int loc = glGetUniformLocation(programID, name.c_str());
        glUniform3fv(loc, 1, &vec[0]);
    };
    unsigned int programID; //from glCreateProgram()


};


#endif //TEXTGAME_SHADER_H
