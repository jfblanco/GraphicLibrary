#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <Configuration.h>
#include <string>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <ShaderManager.h>
#include "../include/ShaderFactoryOpenGL.h"
#include "../shaders/include/ColorShader.h"
#include "../shaders/include/NormalShader.h"
#include "../shaders/include/TextureShader.h"

void checkCompilingStatusLog(GLuint shaderId, GLenum flag) {
    GLint compileStatus = GL_TRUE;
    glGetShaderiv(shaderId, flag,&compileStatus);

    if(compileStatus == GL_FALSE) {
        GLint TotalLenght = 0;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &TotalLenght);
        std::string logs;
        logs.resize(TotalLenght);
        glGetShaderInfoLog(shaderId, TotalLenght, nullptr, &logs[0]);
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, logs.c_str());
    }
}

void checkLinkingStatusLog(GLuint shaderId, GLenum flag) {
    GLint compileStatus = GL_TRUE;
    glGetProgramiv(shaderId, flag, &compileStatus);
    if(compileStatus == GL_FALSE) {
        GLint TotalLenght = 0;
        glGetProgramiv(shaderId, GL_INFO_LOG_LENGTH, &TotalLenght);
        std::string logs;
        logs.resize(TotalLenght);
        glGetProgramInfoLog(shaderId, TotalLenght, nullptr, &logs[0]);
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, logs.c_str());
    }
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

void createShader(ShaderOpenGL* shader, const GLchar *name, const GLchar *vertexPath, const GLchar *fragmentPath) {
    shader->name = name;

    shader->vertexShader = glCreateShader(GL_VERTEX_SHADER);
    shader->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    shader->shaderProgram = glCreateProgram();

    GLint fileSizeVertex;
    GLint fileSizeFragment;

    GLchar* codeVertex = readFile(vertexPath, &fileSizeVertex);
    GLchar* codeFragment = readFile(fragmentPath, &fileSizeFragment);

    glShaderSource(shader->vertexShader, 1, &codeVertex, nullptr);
    glShaderSource(shader->fragmentShader, 1, &codeFragment, nullptr);

    glCompileShader(shader->vertexShader);
    glCompileShader(shader->fragmentShader);

    checkCompilingStatusLog(shader->vertexShader, GL_COMPILE_STATUS);
    checkCompilingStatusLog(shader->fragmentShader, GL_COMPILE_STATUS);

    glAttachShader(shader->shaderProgram, shader->vertexShader);
    glAttachShader(shader->shaderProgram, shader->fragmentShader);

    glLinkProgram(shader->shaderProgram);
    checkLinkingStatusLog(shader->shaderProgram, GL_LINK_STATUS);

    glUseProgram(shader->shaderProgram);
    shader->findUniformVariables();
    shader->findVertexAttributeVariables();
    if(glIsProgram(shader->shaderProgram) == GL_FALSE) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[ShaderFactoryOpenGL] [    Error");
    }
}

void ShaderFactoryOpenGL::init(Configuration *configuration, ShaderManager *shaderManager) {
    std::string path = configuration->getPropertyAsString("shadersFolder");
    std::string message("[ShaderFactoryOpenGL] Loading: ");
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, message.append(path).c_str());

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "[ShaderFactoryOpenGL] [    Loading Simple Shader]");

    auto* colorShader = new ColorShader();
    auto* normalShader = new NormalShader();
    auto* textureShader = new TextureShader();

    createShader(colorShader, "color", (path + "/simple.vert").c_str(), (path + "/simple.frag").c_str());
    createShader(normalShader, "normals", (path + "/normal.vert").c_str(), (path + "/normal.frag").c_str());
    createShader(textureShader, "texture", (path + "/texture.vert").c_str(), (path + "/texture.frag").c_str());

    shaderManager->addShader(colorShader);
    shaderManager->addShader(normalShader);
    shaderManager->addShader(textureShader);

    glUseProgram(0);
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "[ShaderFactoryOpenGL] [    Simple Shader Loaded]");

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "[ShaderFactoryOpenGL] Shaders loading complete");
}

void ShaderFactoryOpenGL::destroy() {

}
