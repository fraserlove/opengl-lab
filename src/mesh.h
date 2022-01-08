#pragma once

#include <objloader.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

struct Vertex {
private:
    glm::vec3 pos;
    glm::vec2 texCoord;
    glm::vec3 normal;

public:
    Vertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& normal = glm::vec3(0, 0, 0)) {
        this->pos = pos;
        this->texCoord = texCoord;
        this->normal = normal;
    }

    inline glm::vec3* GetPos() { return &pos; }
    inline glm::vec2* GetTexCoord() { return &texCoord; }
    inline glm::vec3* GetNormal() { return &normal; }
};

class Mesh {
private:
    enum {
        POSITION_VB,
        TEXCOORD_VB,
        NORMAL_VB,
        INDEX_VB,
        NUM_BUFFERS
    };

    GLuint vertexArrayObject;
    GLuint vertexArrayBuffers[NUM_BUFFERS];

    unsigned int drawCount;

    void InitMesh(const IndexedModel& model);

public:
    Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
    Mesh(const std::string& fileName);
    virtual ~Mesh();
    
    void Draw();
};