#include "RenderableFactoryOpenGL.h"
#include <GL/glew.h>
#include <vector>

void RenderableFactoryOpenGL::createRenderableBuffers(RenderableOpenGL* _renderable) {
    glGenVertexArrays(1, &(_renderable->vao));
    glBindVertexArray(_renderable->vao);

    GLuint vertexSize = _renderable->renderable->vertices.size();
    glGenBuffers(1, &(_renderable->vertexVBO));
    glBindBuffer(GL_ARRAY_BUFFER, _renderable->vertexVBO);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(GLfloat) * 3 * vertexSize,
                 _renderable->renderable->vertices.data(),
                 GL_STATIC_DRAW);

    glGenBuffers(1, &(_renderable->normalVBO));
    glBindBuffer(GL_ARRAY_BUFFER, _renderable->normalVBO);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(GLfloat) * 3 * _renderable->renderable->normals.size(),
                 _renderable->renderable->normals.data(),
                 GL_STATIC_DRAW);

    glGenBuffers(1, &(_renderable->textureVBO));
    glBindBuffer(GL_ARRAY_BUFFER, _renderable->textureVBO);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(GLfloat) * 2 * _renderable->renderable->texture.size(),
                 _renderable->renderable->texture.data(),
                 GL_STATIC_DRAW);

    GLuint indexSize = _renderable->renderable->index.size();
    glGenBuffers(1, &(_renderable->indexVBO));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _renderable->indexVBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 sizeof(GLuint) * indexSize,
                 _renderable->renderable->index.data(),
                 GL_STATIC_DRAW);
}