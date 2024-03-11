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

void ShaderFactoryOpenGL::init(Configuration *configuration, ShaderManager *shaderManager) {
    std::string path = configuration->getPropertyAsString("shadersFolder");
    std::string message("[ShaderFactoryOpenGL] Loading: ");
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, message.append(path).c_str());

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "[ShaderFactoryOpenGL] [    Loading Simple Shader]");
    auto* colorShader = new ColorShader();
    colorShader->name = "color";

    colorShader->vertexShader = glCreateShader(GL_VERTEX_SHADER);
    colorShader->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    colorShader->shaderProgram = glCreateProgram();

    GLint fileSizeVertex;
    GLint fileSizeFragment;

    GLchar* codeVertex = readFile((path + "/simple.vert").c_str(), &fileSizeVertex);
    GLchar* codeFragment = readFile((path + "/simple.frag").c_str(), &fileSizeFragment);

    glShaderSource(colorShader->vertexShader, 1, &codeVertex, nullptr);
    glShaderSource(colorShader->fragmentShader, 1, &codeFragment, nullptr);

    glCompileShader(colorShader->vertexShader);
    glCompileShader(colorShader->fragmentShader);

    checkCompilingStatusLog(colorShader->vertexShader, GL_COMPILE_STATUS);
    checkCompilingStatusLog(colorShader->fragmentShader, GL_COMPILE_STATUS);

    glAttachShader(colorShader->shaderProgram, colorShader->vertexShader);
    glAttachShader(colorShader->shaderProgram, colorShader->fragmentShader);

    glLinkProgram(colorShader->shaderProgram);
    checkLinkingStatusLog(colorShader->shaderProgram, GL_LINK_STATUS);

    glUseProgram(colorShader->shaderProgram);
    colorShader->findUniformVariables();
    colorShader->findVertexAttributeVariables();
    if(glIsProgram(colorShader->shaderProgram) == GL_FALSE) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[ShaderFactoryOpenGL] [    Error");
    }
    glUseProgram(0);
    shaderManager->addShader(colorShader);
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "[ShaderFactoryOpenGL] [    Simple Shader Loaded]");

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "[ShaderFactoryOpenGL] Shaders loading complete");
}

void ShaderFactoryOpenGL::destroy() {

}
