#ifndef ENGINETEST_GUIBASE_H
#define ENGINETEST_GUIBASE_H

#include <vector>
#include <glm/glm.hpp>
#include <SDLAPI.h>

class GUIBase {
public:
    std::vector<GUIBase*> children;
    glm::vec2 position = glm::vec2(0.0,0.0);

    UnsignedInteger16 vertexUniform = UNSIGNED_INTEGER_MAX_16;
    UnsignedInteger16 textureUniform = UNSIGNED_INTEGER_MAX_16;

    GUIBase();
    ~GUIBase();
    void addChild(GUIBase*);
};


#endif //ENGINETEST_GUIBASE_H
