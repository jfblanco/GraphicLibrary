#include "RenderableFactoryOpenGL.h"
#include <OpenGLAPI.h>

RenderableFactoryOpenGL::RenderableFactoryOpenGL(OpenGLAPI* _openGlApi) {
    this->openGlApi = _openGlApi;
}

void RenderableFactoryOpenGL::createRenderableBuffers(Renderable* _renderable) {
    this->openGlApi->createVAO(&(_renderable->vao));
    this->openGlApi->useVAO(_renderable->vao);

    this->openGlApi->createAndMoveVertexVBO(&(_renderable->vertexVBO), &(_renderable->vertices));
    this->openGlApi->createAndMoveNormalVBO(&(_renderable->normalVBO), &(_renderable->normals));
    this->openGlApi->createAndMoveTextureVBO(&(_renderable->textureVBO), &(_renderable->texture));
    this->openGlApi->createAndMoveTangentVBO(&(_renderable->tangentVBO), &(_renderable->tangent));
    this->openGlApi->createAndMoveBiTangentVBO(&(_renderable->bitangentVBO), &(_renderable->bitangent));
    this->openGlApi->createAndMoveIndexVBO(&(_renderable->indexVBO), &(_renderable->index));
}