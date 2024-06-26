#include "../include/GameEntity.h"

GameEntity::GameEntity() {
    this->position = glm::mat4x4(0.0,0.0,0.0,0.0,
                                 0.0,0.0,0.0,0.0,
                                 0.0,0.0,0.0,0.0,
                                 0.0,0.0,0.0,1.0);

    this->rotation = glm::mat4x4(1.0,0.0,0.0,0.0,
                                 0.0,1.0,0.0,0.0,
                                 0.0,0.0,1.0,0.0,
                                 0.0,0.0,0.0,1.0);

    this->scale =    glm::mat4x4(1.0,0.0,0.0,0.0,
                                 0.0,1.0,0.0,0.0,
                                 0.0,0.0,1.0,0.0,
                                 0.0,0.0,0.0,1.0);
}