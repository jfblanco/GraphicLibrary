#ifndef ENGINETEST_JOINT_H
#define ENGINETEST_JOINT_H

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class Joint {
public:
    glm::quat rotation{};
    glm::vec3 eulerAngles{};
    glm::vec3 scale{};
    glm::vec4 tall{};
    std::string name{};

    UnsignedInteger16 index = UNSIGNED_INTEGER_MAX_16;
    glm::mat4 jointToModelMatrix{};
    glm::mat4 modelToJointMatrix{};
    glm::mat4 poseMatrix{};
    std::vector<glm::vec4> size;

    Joint *parent = nullptr;
    std::vector<UnsignedInteger32> children{};
    std::vector<Joint*> childrenObjects{};

    Joint() = default;
    ~Joint() = default;
};


#endif //ENGINETEST_JOINT_H
