#ifndef ENGINETEST_OPENGLAPI_H
#define ENGINETEST_OPENGLAPI_H

#include <gl/glew.h>
#include <string>
#include <vector>
#include <glm/glm.hpp>

typedef GLuint UnsignedInteger;
typedef GLint Integer;
typedef GLshort ShortInteger;
typedef GLfloat Float;
typedef GLboolean Bool;
typedef const GLchar ShaderString;
typedef const GLfloat ConstFloat;

#define BUFFER_OFFSET(a) ((void*)(a))

class OpenGLAPI {
public:
    OpenGLAPI() = default;
    ~OpenGLAPI() = default;

    void initOpenGL();
    void setShaderProgram(UnsignedInteger);
    void setVertexArray(UnsignedInteger);
    void draw(UnsignedInteger,Integer,UnsignedInteger,Integer,UnsignedInteger,Integer,
              UnsignedInteger,Integer,UnsignedInteger,Integer,UnsignedInteger,UnsignedInteger);
    void clean(Float,Float,Float,Float,Float);
    void generateShaderIds(UnsignedInteger*, UnsignedInteger*, UnsignedInteger*);
    Bool attachAndLinkShaderProgram(UnsignedInteger*, UnsignedInteger*, UnsignedInteger*);
    void compileShaders(UnsignedInteger*, ShaderString*, UnsignedInteger*, ShaderString*);
    void useProgram(UnsignedInteger*);
    void cleanProgram();
    Integer getUniform(UnsignedInteger*, ShaderString*);
    Integer getAttribute(UnsignedInteger*, ShaderString*);
    std::string checkCompilingStatusLog(GLuint shaderId);
    std::string checkLinkingStatusLog(GLuint shaderId);
    void sendUniformMatrix(Integer*, ConstFloat*);
    void sendUniformVector4(Integer*, ConstFloat*);
    void sendUniformVector3(Integer*, ConstFloat*);
    void sendUniformInteger(Integer*, Integer);
    void sendUniformFloat(Integer*, Float);
    void createVAO(UnsignedInteger*);
    void useVAO(UnsignedInteger);
    void createAndMoveVertexVBO(UnsignedInteger*,std::vector<glm::vec3>*);
    void createAndMoveNormalVBO(UnsignedInteger*,std::vector<glm::vec3>*);
    void createAndMoveTextureVBO(UnsignedInteger*,std::vector<glm::vec2>*);
    void createAndMoveTangentVBO(UnsignedInteger*,std::vector<glm::vec3>*);
    void createAndMoveBiTangentVBO(UnsignedInteger*,std::vector<glm::vec3>*);
    void createAndMoveIndexVBO(UnsignedInteger*,std::vector<UnsignedInteger>*);
};


#endif //ENGINETEST_OPENGLAPI_H
