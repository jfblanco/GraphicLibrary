#ifndef ENGINETEST_LIGHT_H
#define ENGINETEST_LIGHT_H

#include <glm/glm.hpp>

class Light {
public:
    glm::vec3 position;
    glm::vec4 color;

    Light();
    ~Light();
};


#endif //ENGINETEST_LIGHT_H
