#ifndef ENGINETEST_SCENE_H
#define ENGINETEST_SCENE_H

#include <glm/glm.hpp>

class Camera;
class Scene {
public:
    glm::mat4x4 projection;
    Camera *camera;

    Scene();
    ~Scene();
};

#endif //ENGINETEST_SCENE_H
