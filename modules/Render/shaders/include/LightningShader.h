#ifndef ENGINETEST_LIGHTNINGSHADER_H
#define ENGINETEST_LIGHTNINGSHADER_H

#include <ShaderOpenGL.h>
#include <glm/glm.hpp>

class Light;
class LightningShader : public ShaderOpenGL {
public:
    LightningShader() = default;
    ~LightningShader() = default;

    Light* ambient;
    Light* diffuse;
    Light* specular;

    Sint16 ambientColor;
    Sint16 diffuseColor;
    Sint16 specularColor;

    Sint16 lightPosition;
    Sint16 viewPosition;

    void findUniformVariables() override;
    void useUniformVariables(RenderingSystem*, Renderable*) override;
};


#endif //ENGINETEST_LIGHTNINGSHADER_H
