#pragma once

#include <GL/glew.h>
#include <string>

class Shader {
private:
    static const unsigned int NUM_SHADERS = 2;
    GLuint program; // numeric reference for shader
    GLuint shaders[NUM_SHADERS];

public:
    Shader(const std::string& fileName);
    virtual ~Shader();

    void Bind();
};