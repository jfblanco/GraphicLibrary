#ifndef ENGINETEST_SHADERMANAGER_H
#define ENGINETEST_SHADERMANAGER_H

#include <string>
#include <map>
#include "../../Render/include/MockShader.h"

class ShaderManager {
public:
    MockShader *mockShader = new MockShader();

    virtual Shader* findShader(const std::string&)=0;
    virtual void addShader(Shader* shader)=0;
    ShaderManager() = default;
    ~ShaderManager() = default;
};


#endif //ENGINETEST_SHADERMANAGER_H
