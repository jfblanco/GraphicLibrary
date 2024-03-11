#ifndef ENGINETEST_SHADEROPENGL_H
#define ENGINETEST_SHADEROPENGL_H

#include <Shader.h>
#include <GL/glew.h>

class ShaderOpenGL : public Shader {
public:
    GLuint shaderProgram;
    GLuint vertexShader;
    GLuint fragmentShader;

    ShaderOpenGL() = default;
    ~ShaderOpenGL() = default;
};

#endif //ENGINETEST_SHADEROPENGL_H
