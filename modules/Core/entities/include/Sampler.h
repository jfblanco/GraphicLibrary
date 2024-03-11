#ifndef ENGINETEST_SAMPLER_H
#define ENGINETEST_SAMPLER_H

#include <glm/vec3.hpp>
#include <glm/gtx/quaternion.hpp>

class Skin;
class Sampler {
public:
    Sampler() = default;
    ~Sampler() = default;

    glm::quat startRotation{};
    glm::vec3 startEuler{};
    glm::vec3 startPosition{};

    glm::quat endRotation{};
    glm::vec3 endEuler{};
    glm::vec3 endPosition{};

    glm::quat interpolationVector{};
    glm::quat currentQuaternionRotation{};

    float start = 0.0f;
    float end = 0.0f;
    float timeDifference = 0.0f;
    bool emptySampler = false;

//    void calculateSamplerMatrix(Skin*,glm::mat4*,glm::mat4*,uint16_t,float);
};

#endif //ENGINETEST_SAMPLER_H
