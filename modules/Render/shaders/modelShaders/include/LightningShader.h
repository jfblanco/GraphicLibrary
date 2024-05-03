#ifndef ENGINETEST_LIGHTNINGSHADER_H
#define ENGINETEST_LIGHTNINGSHADER_H

#include <Shader.h>
#include <glm/glm.hpp>

class Light;
class LightningShader : public Shader {
public:
    LightningShader() = default;
    ~LightningShader() = default;

    Light* ambient = nullptr;
    Light* diffuse = nullptr;
    Light* specular = nullptr;

    Sint16 ambientColorUBO = SDL_MAX_UINT16;
    Sint16 diffuseColorUBO = SDL_MAX_UINT16;
    Sint16 specularColorUBO = SDL_MAX_UINT16;

    Sint16 lightPositionUBO = SDL_MAX_UINT16;
    Sint16 viewPositionUBO = SDL_MAX_UINT16;

    void findUniformVariables() override;
    void useUniformVariables(RenderingSystem*, Renderable*) override;
};


#endif //ENGINETEST_LIGHTNINGSHADER_H
