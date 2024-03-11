#ifndef ENGINETEST_ANIMATION_H
#define ENGINETEST_ANIMATION_H

#include <vector>
#include <string>
#include <glm/mat4x4.hpp>

class AnimatedBone;
class Skin;
class Animation {
public:
    Animation() = default;
    ~Animation() = default;

    std::string name;
    std::vector<AnimatedBone*> animatedBones;
    float startTime;
    float endTime;

//    void updateAnimationMatrix(Skin*,glm::mat4*,glm::mat4*,uint16_t);
};


#endif //ENGINETEST_ANIMATION_H
