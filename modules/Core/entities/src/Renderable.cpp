#include "../include/Renderable.h"
#include <glm/detail/type_quat.hpp>
#include <glm/gtx/quaternion.hpp>

void Renderable::setPosition(GLfloat x, GLfloat y, GLfloat z) {
    this->position = glm::vec4(x, y, z, 1.0);
    this->updateModelMatrix();
}

void Renderable::setRotation(GLfloat roll, GLfloat pitch, GLfloat yaw) {
    this->eulerAngles = glm::vec3(roll, pitch, yaw);
    this->rotation = glm::quat(this->eulerAngles);
    this->updateModelMatrix();
}

void Renderable::updateModelMatrix() {
    auto a = glm::translate(glm::mat4x4(1.0), glm::vec3(this->position));
    this->modelMatrix = glm::toMat4(this->rotation)
                        * glm::translate(glm::mat4x4(1.0), glm::vec3(this->position))
                        * glm::scale(glm::mat4x4(1.0), glm::vec3(this->scale));
}
