#ifndef ENGINETEST_ANIMATEDBONE_H
#define ENGINETEST_ANIMATEDBONE_H

#include <vector>
#include <SDL2/SDL.h>
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
    Uint16 currentSamplerIndex = 0;

//    void calculateSamplerMatrix(Skin*,glm::mat4*,glm::mat4*, Uint16,float);
};


#endif //ENGINETEST_ANIMATEDBONE_H
