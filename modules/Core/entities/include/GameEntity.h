#ifndef ENGINETEST_GAMEENTITY_H
#define ENGINETEST_GAMEENTITY_H

#include <glm/glm.hpp>
#include <vector>
#include <string>

class Renderable;
class GameEntity {
public:
    std::string name;
    glm::mat4x4 position;
    glm::mat4x4 rotation;
    glm::mat4x4 scale;

    std::vector<Renderable*> renderables;

    GameEntity();
    ~GameEntity() = default;
};


#endif //ENGINETEST_GAMEENTITY_H
