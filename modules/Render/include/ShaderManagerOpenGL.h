#ifndef ENGINETEST_SHADERMANAGEROPENGL_H
#define ENGINETEST_SHADERMANAGEROPENGL_H

#include <ShaderManager.h>
#include "Shader.h"
#include <map>

class ShaderManagerOpenGL : public ShaderManager {
public:
    std::map<std::string, Shader*> shaders;

    Shader* findShader(const std::string&) override;
    void addShader(Shader* shader) override;

    ShaderManagerOpenGL() = default;
    ~ShaderManagerOpenGL() = default;
};


#endif //ENGINETEST_SHADERMANAGEROPENGL_H
