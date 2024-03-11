#ifndef ENGINETEST_JOINT_H
#define ENGINETEST_JOINT_H

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <SDL2/SDL.h>

class Joint {
public:
    glm::quat rotation{};
    glm::vec3 eulerAngles{};
    glm::vec3 scale{};
    glm::vec4 tall{};
    std::string name{};

    Uint16 index = 0;
    glm::mat4 jointToModelMatrix{};
    glm::mat4 modelToJointMatrix{};
    glm::mat4 poseMatrix{};
    std::vector<glm::vec4> size;

    Joint *parent = nullptr;
    std::vector<Uint32> children{};
    std::vector<Joint*> childrenObjects{};

    Joint() = default;
    ~Joint() = default;
};


#endif //ENGINETEST_JOINT_H
