#pragma once

#include <GL/glew.h>
#include <string>

class Texture {
private:
    GLuint texture;

public:
    Texture(const std::string& fileName);
    virtual ~Texture();

    void Bind(unsigned int unit);
};