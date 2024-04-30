#ifndef ENGINETEST_SHADEROPENGL_H
#define ENGINETEST_SHADEROPENGL_H

#include <Shader.h>
#include <SDL2/SDL.h>
#include <GL/glew.h>

class ShaderOpenGL : public Shader {
public:
    GLuint shaderProgram;
    GLuint vertexShader;
    GLuint fragmentShader;

    Sint16 projectionModelViewUniform;
    Sint16 modelMatrixUniform;
    Sint16 viewMatrixUniform;
    Sint16 vertexAttribute;
    Sint16 normalAttribute;
    Sint16 uvCoordAttribute;
    Sint16 tangentAttribute;
    Sint16 bitangentAttribute;

    Sint16 albedoUniform;
    Sint16 normalUniform;
    Sint16 heightUniform;
    Sint16 ambientOcclusionUniform;
    Sint16 roughtnessOcclusionUniform;
    Sint16 metallicUniform;

    ShaderOpenGL() = default;
    ~ShaderOpenGL() = default;

    void findUniformVariables() override;
    void useUniformVariables(RenderingSystem*, Renderable*) override;
    void findVertexAttributeVariables() override;
};

#endif //ENGINETEST_SHADEROPENGL_H
