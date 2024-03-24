#ifndef ENGINETEST_MATERIALOPENGL_H
#define ENGINETEST_MATERIALOPENGL_H

#include <string>
#include <Material.h>
#include "ShaderOpenGL.h"

class Shader;
class RenderableOpenGL;
class MaterialOpenGL : public Material {
public:
    ShaderOpenGL *shaderOpenGL;
    GLuint albedo;
    GLuint metalic;
    GLuint roughness;
    GLuint normal;
    GLuint ambientOcclusion;

    void prepareMaterial(RenderableOpenGL*);
    void setTextures();
    explicit MaterialOpenGL(const char* _name, ShaderOpenGL* _shader) : Material(_name) { this->shaderOpenGL = _shader; };
    ~MaterialOpenGL() = default;
};

#endif //ENGINETEST_MATERIALOPENGL_H
