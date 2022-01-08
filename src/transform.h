#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Transform {
private:
    glm::vec3 pos;
    glm::vec3 rot;
    glm::vec3 scale;

public:
    Transform(const glm::vec3& pos = glm::vec3(0.0, 0.0, 0.0), const glm::vec3& rot = glm::vec3(0.0, 0.0, 0.0), const glm::vec3& scale = glm::vec3(1.0, 1.0, 1.0)) {
       
        this->pos = pos;
        this->rot = rot;
        this->scale = scale;
    }

    inline glm::mat4 GetModel() const {

        glm::mat4 posMatrix = glm::translate(pos);
        glm::mat4 rotX = glm::rotate(rot.x, glm::vec3(1.0, 0.0, 0.0));
        glm::mat4 rotY = glm::rotate(rot.y, glm::vec3(0.0, 1.0, 0.0));
        glm::mat4 rotZ = glm::rotate(rot.z, glm::vec3(0.0, 0.0, 1.0));
        glm::mat4 scaleMatrix = glm::scale(scale);

        glm::mat4 rotMatrix = rotZ * rotY * rotX;

        return posMatrix * rotMatrix * scaleMatrix;
    }

    inline glm::vec3& GetPos() { return pos; }
    inline glm::vec3& GetRot() { return rot; }
    inline glm::vec3& GetScale() { return scale; }

    inline void SetPos(const glm::vec3& pos) { this->pos = pos; }
    inline void SetRot(const glm::vec3& rot) { this->rot = rot; }
    inline void SetScale(const glm::vec3& scale) { this->scale = scale; }

    inline void SetScale(const float scale) { this->scale = glm::vec3(scale, scale, scale); }

};