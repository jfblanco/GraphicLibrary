#ifndef ENGINETEST_SHADERFACTORYOPENGL_H
#define ENGINETEST_SHADERFACTORYOPENGL_H

#include <ShaderFactory.h>
#include <SDLAPI.h>
#include <OpenGLAPI.h>

class Shader;
class Configuration;
class ShaderFactoryOpenGL : public ShaderFactory {
public:
    SDLAPI* sdlApi = nullptr;
    OpenGLAPI* oglApi = nullptr;

    ShaderFactoryOpenGL(SDLAPI*, OpenGLAPI*);
    ~ShaderFactoryOpenGL() = default;

    void init(Configuration*, ShaderManager*) override;
    void createShader(Shader*, const char *, const char *, const char *);
    void destroy() override;
};


#endif //ENGINETEST_SHADERFACTORYOPENGL_H
