#ifndef ENGINETEST_RENDERABLE_OPENGL_H
#define ENGINETEST_RENDERABLE_OPENGL_H

#include <Renderable.h>
#include <GL/glew.h>

class MaterialOpenGL;
class ShaderManager;
class RenderableOpenGL {
public:
    Renderable *renderable;
    MaterialOpenGL *materialOpenGL;
    GLuint vao;
    GLuint vertexVBO;
    GLuint normalVBO;
    GLuint textureVBO;
    GLuint indexVBO;

    RenderableOpenGL(Renderable *_renderable) { this->renderable = _renderable; };
    void prepareMaterial(ShaderManager*);
    ~RenderableOpenGL() = default;

};

#endif //ENGINETEST_RENDERABLE_OPENGL_H
