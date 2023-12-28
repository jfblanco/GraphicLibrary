//
// Created by Usuario on 12/27/2023.
//

#include "../include/GameBaseEntity.h"

GameBaseEntity::GameBaseEntity(){
    position = glm::vec3(0.0, 0.0, 0.0);
    scale = glm::vec3(0.0, 0.0, 0.0);
    rotation = glm::mat4x4 (1.0, 0.0, 0.0, 0.0,
                            0.0, 1.0, 0.0, 0.0,
                            0.0, 0.0, 1.0, 0.0,
                            0.0, 0.0, 0.0, 1.0);
}

GameBaseEntity::~GameBaseEntity() {

}