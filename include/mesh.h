#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

struct Vertex {
private:
    glm::vec3 pos;
    glm::vec2 texCoord;

public:
    Vertex(const glm::vec3& pos, const glm::vec2& texCoord) {
        this->pos = pos;
        this->texCoord = texCoord;
    }

    inline glm::vec3* GetPos() { return &pos; }
    inline glm::vec2* GetTexCoord() { return &texCoord; }
};

class Mesh {
private:
    enum {
        POSITION_VB,
        TEXCOORD_VB,
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