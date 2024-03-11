#ifndef ENGINETEST_SHADERFACTORYOPENGL_H
#define ENGINETEST_SHADERFACTORYOPENGL_H

#include <ShaderFactory.h>

class Shader;
class Configuration;
class ShaderFactoryOpenGL : public ShaderFactory {
public:
    ShaderFactoryOpenGL() = default;
    ~ShaderFactoryOpenGL() = default;

    void init(Configuration*, ShaderManager*) override;
    void destroy() override;
};


#endif //ENGINETEST_SHADERFACTORYOPENGL_H
