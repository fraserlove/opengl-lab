#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

class Vertex {
private:
    glm::vec3 pos;

public:
    Vertex(const glm::vec3& pos) {
        this->pos = pos;
    }
};

class Mesh {
private:
    enum {
        POSITION_VB,
        NUM_BUFFERS
    };

    GLuint vertexArrayObject;
    GLuint vertexArrayBuffers[NUM_BUFFERS];

    unsigned int drawCount;

public:
    Mesh(Vertex* vertices, unsigned int numVertices);
    virtual ~Mesh();
    
    void Draw();
};