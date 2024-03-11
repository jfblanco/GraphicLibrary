#ifndef ENGINETEST_CAMERA_H
#define ENGINETEST_CAMERA_H

#include <glm/glm.hpp>

class Camera {
public:
    glm::vec3 point = glm::vec3(0.0f,0.0f,0.0f);
    glm::vec3 position = glm::vec3(0.0f,2.0f,-2.0f);
    glm::vec3 orientation = glm::vec3(0.0f,1.0f,0.0f);
    glm::mat4x4 viewMatrix;

    Camera() = default;
    ~Camera() = default;
};

#endif //ENGINETEST_CAMERA_H
