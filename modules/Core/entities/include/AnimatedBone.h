#ifndef ENGINETEST_ANIMATEDBONE_H
#define ENGINETEST_ANIMATEDBONE_H

#include <vector>
#include <SDLAPI.h>
#include <glm/mat4x4.hpp>

class Sampler;
class Skin;
class AnimatedBone {
public:
    AnimatedBone() = default;
    ~AnimatedBone() = default;

    std::vector<Sampler*> samplers;
    Sampler* currentSampler{};
    float currentTime = 0.0f;
    UnsignedInteger16 currentSamplerIndex = UNSIGNED_INTEGER_MAX_16;

//    void calculateSamplerMatrix(Skin*,glm::mat4*,glm::mat4*, Uint16,float);
};


#endif //ENGINETEST_ANIMATEDBONE_H
