#ifndef ENGINETEST_RENDERABLEFACTORYOPENGL_H
#define ENGINETEST_RENDERABLEFACTORYOPENGL_H

#include "Renderable.h"

class OpenGLAPI;
class RenderableFactoryOpenGL {
public:
    OpenGLAPI* openGlApi;

    RenderableFactoryOpenGL(OpenGLAPI*);
    ~RenderableFactoryOpenGL() = default;

    void createRenderableBuffers(Renderable*);
//    void createVertexBufferObject(GLuint*, const void*, );
};


#endif //ENGINETEST_RENDERABLEFACTORYOPENGL_H
