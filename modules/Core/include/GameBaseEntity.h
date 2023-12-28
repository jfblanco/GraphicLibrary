//
// Created by Usuario on 12/27/2023.
//

#ifndef ENGINETEST_GAMEBASEENTITY_H
#define ENGINETEST_GAMEBASEENTITY_H

#include "glm/glm.hpp"

class GameBaseEntity {
    public:
        glm::vec3 position;
        glm::mat4x4 rotation;
        glm::vec3 scale;

        GameBaseEntity();
        ~GameBaseEntity();
};


#endif //ENGINETEST_GAMEBASEENTITY_H
