#ifndef ENGINETEST_GAMEENTITY_H
#define ENGINETEST_GAMEENTITY_H

#include "../../external/glm/glm.hpp"

class GameEntity {
public:
    glm::mat4x4 position;
    glm::mat4x4 rotation;
    glm::mat4x4 scale;

    GameEntity();
    ~GameEntity() = default;
};


#endif //ENGINETEST_GAMEENTITY_H
