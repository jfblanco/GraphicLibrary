#ifndef ENGINETEST_SKIN_H
#define ENGINETEST_SKIN_H

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/detail/type_quat.hpp>

class Joint;
class Skin {
public:
    std::string name;
    std::vector<Joint*> joints{};
    glm::vec3 origin{};
    glm::quat rotation{};
    glm::vec4 position{};
    glm::mat4 worldToSkinMatrix{};

    std::vector<glm::mat4> inversedMatrixArray;
    std::vector<glm::mat4> positionMatrixArray;

    std::map<std::string, Animation*> animations;
    std::vector<glm::mat4> currentAnimationMatrices;
    std::vector<glm::mat4> modelToJointMatrices;


};

#endif //ENGINETEST_SKIN_H
