#ifndef ENGINETEST_RENDERABLE_OPENGL_H
#define ENGINETEST_RENDERABLE_OPENGL_H

#include <Renderable.h>
#include <GL/glew.h>

class RenderableOpenGL {
public:
    Renderable *renderable;
    GLuint vao;
    GLuint vertexVBO;
    GLuint normalVBO;
    GLuint textureVBO;
    GLuint indexVBO;

    RenderableOpenGL(Renderable *_renderable) { this->renderable = _renderable; };
    ~RenderableOpenGL() = default;

};

#endif //ENGINETEST_RENDERABLE_OPENGL_H
