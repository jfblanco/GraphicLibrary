#include "../include/OpenGLAPI.h"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>

void OpenGLAPI::initOpenGL() {
    glewExperimental = GL_TRUE;
    const GLenum initCode = glewInit();
    if (initCode != GLEW_OK){
        exit(0);
    }
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glDepthFunc(GL_LESS);
}

void OpenGLAPI::setShaderProgram(UnsignedInteger _shaderId) {
    glUseProgram(_shaderId);
}

void OpenGLAPI::setVertexArray(UnsignedInteger _vertexArrayObject) {
    glBindVertexArray(_vertexArrayObject);
}

void OpenGLAPI::generateShaderIds(GLuint* _vertexShaderId, GLuint* _fragmentShaderId, GLuint* _programShaderId) {
    *_vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    *_fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    *_programShaderId = glCreateProgram();
}

unsigned long getFileLength(std::ifstream& file)
{
    if(!file.good())
        return 0;
    GLulong pos = file.tellg();
    file.seekg(0,std::ios::end);
    GLulong len = file.tellg();
    file.seekg(std::ios::beg);
    return len;
}

char* readFile(const GLchar* _file, GLint* lenght){
    std::ifstream file;
    file.open(_file, std::ios::in);
    *lenght = getFileLength(file);

    if(*lenght == 0)
        return new GLchar[1]{' '};
    else{
        char* ShaderSource = new GLchar[*lenght];
        GLuint i=0;
        while (file.good())
        {
            ShaderSource[i] = file.get();
            i++;
        }
        ShaderSource[i-1] = '\0';
        return ShaderSource;
    }
}

void OpenGLAPI::compileShaders(UnsignedInteger* _vertexShaderId, const GLchar* _vertexShaderPath,
                               UnsignedInteger* _fragmentShaderId, const GLchar* _fragmentShaderPath) {
    GLint fileSizeVertex;
    GLint fileSizeFragment;

    GLchar* codeVertex = readFile(_vertexShaderPath, &fileSizeVertex);
    GLchar* codeFragment = readFile(_fragmentShaderPath, &fileSizeFragment);

    glShaderSource(*_vertexShaderId, 1, &codeVertex, nullptr);
    glShaderSource(*_fragmentShaderId, 1, &codeFragment, nullptr);

    glCompileShader(*_vertexShaderId);
    glCompileShader(*_fragmentShaderId);
}

void OpenGLAPI::clean(Float _red, Float _green, Float _blue, Float _alpha, Float _depth) {
    glClearColor(_red, _green, _blue, _alpha);
    glClearDepth(_depth);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

std::string OpenGLAPI::checkCompilingStatusLog(GLuint shaderId) {
    GLint compileStatus = GL_TRUE;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compileStatus);
    std::string logs;
    if(compileStatus == GL_FALSE) {
        GLint TotalLenght = 0;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &TotalLenght);
        logs.resize(TotalLenght);
        glGetShaderInfoLog(shaderId, TotalLenght, nullptr, &logs[0]);
    }
    return logs;
}

GLboolean OpenGLAPI::attachAndLinkShaderProgram(GLuint* _vertexShaderId, GLuint* _fragmentShaderId, GLuint* _programShaderId) {
    glAttachShader(*_programShaderId, *_vertexShaderId);
    glAttachShader(*_programShaderId, *_fragmentShaderId);
    glLinkProgram(*_programShaderId);
    return glIsProgram(*_programShaderId);
}

void OpenGLAPI::useProgram(GLuint* _programShaderId) {
    glUseProgram(*_programShaderId);
}

void OpenGLAPI::cleanProgram() {
    glUseProgram(0);
}

GLint OpenGLAPI::getUniform(GLuint* _shaderProgramId, ShaderString* _uniformVarName) {
    return glGetUniformLocation(*_shaderProgramId, _uniformVarName);
}

GLint OpenGLAPI::getAttribute(GLuint* _shaderProgramId, ShaderString* _vertexAttributeName) {
    return glGetAttribLocation(*_shaderProgramId, _vertexAttributeName);
}

std::string OpenGLAPI::checkLinkingStatusLog(GLuint shaderId) {
    GLint compileStatus = GL_TRUE;
    glGetProgramiv(shaderId, GL_LINK_STATUS, &compileStatus);
    std::string logs;
    if(compileStatus == GL_FALSE) {
        GLint TotalLenght = 0;
        glGetProgramiv(shaderId, GL_INFO_LOG_LENGTH, &TotalLenght);
        logs.resize(TotalLenght);
        glGetProgramInfoLog(shaderId, TotalLenght, nullptr, &logs[0]);
    }
    return logs;
}

void OpenGLAPI::draw(UnsignedInteger vertVBO, Integer vertAttribute,
                     UnsignedInteger normVBO, Integer normAttribute,
                     UnsignedInteger textVBO, Integer textAttribute,
                     UnsignedInteger bitangVBO, Integer bittangAttribute,
                     UnsignedInteger tangVBO, Integer tangAttribute,
                     UnsignedInteger indexVBO, UnsignedInteger indexSize) {
    glBindBuffer(GL_ARRAY_BUFFER, vertVBO);
    glVertexAttribPointer(vertAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), BUFFER_OFFSET(0));
    glEnableVertexAttribArray(vertAttribute);

    glBindBuffer(GL_ARRAY_BUFFER, normVBO);
    glVertexAttribPointer(normAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), BUFFER_OFFSET(0));
    glEnableVertexAttribArray(normAttribute);

    glBindBuffer(GL_ARRAY_BUFFER, tangVBO);
    glVertexAttribPointer(tangAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), BUFFER_OFFSET(0));
    glEnableVertexAttribArray(tangAttribute);

    glBindBuffer(GL_ARRAY_BUFFER, bitangVBO);
    glVertexAttribPointer(bittangAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), BUFFER_OFFSET(0));
    glEnableVertexAttribArray(bittangAttribute);

    glBindBuffer(GL_ARRAY_BUFFER, textVBO);
    glVertexAttribPointer(textAttribute, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), BUFFER_OFFSET(0));
    glEnableVertexAttribArray(textAttribute);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);
    glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, NULL);
}

void OpenGLAPI::sendUniformMatrix(Integer *_uniformVariable, ConstFloat* _matrixPointer) {
    glUniformMatrix4fv(*_uniformVariable, 1, GL_FALSE, _matrixPointer);
}

void OpenGLAPI::sendUniformVector4(Integer *_uniformVariable, ConstFloat* _vectorPointer) {
    glUniform4fv(*_uniformVariable, 1, _vectorPointer);
}

void OpenGLAPI::sendUniformVector3(Integer *_uniformVariable, ConstFloat* _vectorPointer) {
    glUniform3fv(*_uniformVariable, 1, _vectorPointer);
}

void OpenGLAPI::sendUniformInteger(Integer *_uniformVariable, Integer _value) {
    glUniform1i(*_uniformVariable, _value);
}

void OpenGLAPI::sendUniformFloat(Integer *_uniformVariable, Float _value) {
    glUniform1f(*_uniformVariable, _value);
}

void OpenGLAPI::createVAO(UnsignedInteger* _vao) {
    glGenVertexArrays(1, _vao);
}

void OpenGLAPI::useVAO(UnsignedInteger _vao) {
    glBindVertexArray(_vao);
}

void OpenGLAPI::createAndMoveVertexVBO(UnsignedInteger * _vertexVBO, std::vector<glm::vec3>* _vertexVector) {
    glGenBuffers(1, _vertexVBO);
    glBindBuffer(GL_ARRAY_BUFFER, *_vertexVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * (*_vertexVector).size(), (*_vertexVector).data(), GL_STATIC_DRAW);
}

void OpenGLAPI::createAndMoveNormalVBO(UnsignedInteger * _normalVBO, std::vector<glm::vec3>* _normalVector) {
    glGenBuffers(1, _normalVBO);
    glBindBuffer(GL_ARRAY_BUFFER, *_normalVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * (*_normalVector).size(), (*_normalVector).data(), GL_STATIC_DRAW);
}

void OpenGLAPI::createAndMoveTangentVBO(UnsignedInteger * _tangentVBO, std::vector<glm::vec3>* _tangentVector) {
    glGenBuffers(1, _tangentVBO);
    glBindBuffer(GL_ARRAY_BUFFER, *_tangentVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * (*_tangentVector).size(), (*_tangentVector).data(), GL_STATIC_DRAW);
}

void OpenGLAPI::createAndMoveBiTangentVBO(UnsignedInteger * _biTangentVBO, std::vector<glm::vec3>* _biTangentVector) {
    glGenBuffers(1, _biTangentVBO);
    glBindBuffer(GL_ARRAY_BUFFER, *_biTangentVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * (*_biTangentVector).size(), (*_biTangentVector).data(), GL_STATIC_DRAW);
}

void OpenGLAPI::createAndMoveTextureVBO(UnsignedInteger * _textureVBO, std::vector<glm::vec2>* _textureVector) {
    glGenBuffers(1, _textureVBO);
    glBindBuffer(GL_ARRAY_BUFFER, *_textureVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * (*_textureVector).size(), (*_textureVector).data(), GL_STATIC_DRAW);
}

void OpenGLAPI::createAndMoveIndexVBO(UnsignedInteger * _indexVBO, std::vector<UnsignedInteger>* _indexVector) {
    glGenBuffers(1, _indexVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *_indexVBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(GLuint) * (*_indexVector).size(),(*_indexVector).data(),GL_STATIC_DRAW);
}