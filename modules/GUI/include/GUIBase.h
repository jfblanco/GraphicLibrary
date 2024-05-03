#ifndef ENGINETEST_GUIBASE_H
#define ENGINETEST_GUIBASE_H

#include <vector>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>

class GUIBase {
public:
    std::vector<GUIBase*> children;
    glm::vec2 position = glm::vec2(0.0,0.0);

    Uint16 vertexUniform;
    Uint16 textureUniform;

    GUIBase();
    ~GUIBase();
    void addChild(GUIBase*);
};


#endif //ENGINETEST_GUIBASE_H
