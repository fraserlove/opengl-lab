#pragma once

#include "transform.h"

#include <GL/glew.h>
#include <string>

class Shader {
private:
    static const unsigned int NUM_SHADERS = 2;

    enum {
        TRANSFORM_U,
        NUM_UNIFORMS
    };

    GLuint program; // numeric reference for shader
    GLuint shaders[NUM_SHADERS];
    GLuint uniforms[NUM_UNIFORMS];

public:
    Shader(const std::string& fileName);
    virtual ~Shader();

    void Bind();
    void Update(const Transform& transform);
};