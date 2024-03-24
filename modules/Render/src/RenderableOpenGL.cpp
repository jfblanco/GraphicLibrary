#include "../include/RenderableOpenGL.h"
#include "../include/ShaderOpenGL.h"
#include "../include/MaterialOpenGL.h"
#include <ShaderManager.h>

void RenderableOpenGL::prepareMaterial(ShaderManager *_shaderManager) {
    auto* material = new MaterialOpenGL(this->renderable->material->name.c_str(), (ShaderOpenGL*) _shaderManager->findShader(this->renderable->material->name.c_str()));
    this->materialOpenGL = material;
    material->prepareMaterial(this);
}