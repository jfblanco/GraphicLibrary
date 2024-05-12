#ifndef ENGINETEST_SHADER_H
#define ENGINETEST_SHADER_H

#include "../include/Shader.h"
#include <string>
#include <SDLAPI.h>
#include <OpenGLAPI.h>

class RenderingSystem;
class Texture;
class Renderable;
class OpenGLAPI;
class Shader {
public:
    std::string name;

    UnsignedInteger32 shaderProgram = 0;
    UnsignedInteger32 vertexShader = 0;
    UnsignedInteger32 fragmentShader = 0;

    Integer32 projectionModelViewUniform = INTEGER_MAX_32;
    Integer32 modelMatrixUniform = INTEGER_MAX_32;
    Integer32 viewMatrixUniform = INTEGER_MAX_32;
    Integer32 vertexAttribute = INTEGER_MAX_32;
    Integer32 normalAttribute = INTEGER_MAX_32;
    Integer32 uvCoordAttribute = INTEGER_MAX_32;
    Integer32 tangentAttribute = INTEGER_MAX_32;
    Integer32 bitangentAttribute = INTEGER_MAX_32;

    Integer32 albedoUBO = INTEGER_MAX_32;
    Integer32 normalUBO = INTEGER_MAX_32;
    Integer32 heightUBO = INTEGER_MAX_32;
    Integer32 ambientOcclusionUBO = INTEGER_MAX_32;
    Integer32 roughtnessOcclusionUBO = INTEGER_MAX_32;
    Integer32 metallicUBO = INTEGER_MAX_32;

    Shader() = default;
    ~Shader() = default;

    virtual void findUniformVariables(OpenGLAPI*);
    virtual void useUniformVariables(RenderingSystem*, OpenGLAPI*, Renderable*);
    virtual void findVertexAttributeVariables(OpenGLAPI*);
};

#endif //ENGINETEST_SHADER_H
