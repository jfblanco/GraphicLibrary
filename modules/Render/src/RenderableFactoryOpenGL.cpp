#include "RenderableFactoryOpenGL.h"
#include <GL/glew.h>

void RenderableFactoryOpenGL::createRenderableBuffers(Renderable* _renderable) {
    glGenVertexArrays(1, (GLuint*)&(_renderable->vao));
    glBindVertexArray(_renderable->vao);

    GLuint vertexSize = _renderable->vertices.size();
    glGenBuffers(1, (GLuint*)&(_renderable->vertexVBO));
    glBindBuffer(GL_ARRAY_BUFFER, _renderable->vertexVBO);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(GLfloat) * 3 * vertexSize,
                 _renderable->vertices.data(),
                 GL_STATIC_DRAW);

    glGenBuffers(1, (GLuint*)&(_renderable->normalVBO));
    glBindBuffer(GL_ARRAY_BUFFER, _renderable->normalVBO);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(GLfloat) * 3 * _renderable->normals.size(),
                 _renderable->normals.data(),
                 GL_STATIC_DRAW);

    glGenBuffers(1, (GLuint*)&(_renderable->tangentVBO));
    glBindBuffer(GL_ARRAY_BUFFER, _renderable->tangentVBO);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(GLfloat) * 3 * _renderable->tangent.size(),
                 _renderable->tangent.data(),
                 GL_STATIC_DRAW);

    glGenBuffers(1, (GLuint*)&(_renderable->bitangentVBO));
    glBindBuffer(GL_ARRAY_BUFFER, _renderable->bitangentVBO);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(GLfloat) * 3 * _renderable->bitangent.size(),
                 _renderable->bitangent.data(),
                 GL_STATIC_DRAW);

    glGenBuffers(1, (GLuint*)&(_renderable->textureVBO));
    glBindBuffer(GL_ARRAY_BUFFER, _renderable->textureVBO);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(GLfloat) * 2 * _renderable->texture.size(),
                 _renderable->texture.data(),
                 GL_STATIC_DRAW);

    GLuint indexSize = _renderable->index.size();
    glGenBuffers(1, (GLuint*)&(_renderable->indexVBO));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _renderable->indexVBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 sizeof(GLuint) * indexSize,
                 _renderable->index.data(),
                 GL_STATIC_DRAW);
}