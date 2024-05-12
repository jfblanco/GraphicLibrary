#include <SDLAPI.h>
#include <OpenGLAPI.h>
#include <Configuration.h>
#include <string>
#include <ShaderManager.h>
#include "../include/ShaderFactoryOpenGL.h"
#include <ColorShader.h>
#include <NormalShader.h>
#include <TextureShader.h>
#include <LightningShader.h>
#include <NormalMappingShader.h>
#include <ParallaxMappingShader.h>

ShaderFactoryOpenGL::ShaderFactoryOpenGL(SDLAPI* _sdlApi, OpenGLAPI* _oglApi) {
    this->sdlApi = _sdlApi;
    this->oglApi = _oglApi;
}

void ShaderFactoryOpenGL::createShader(Shader* shader, const char *name, const char *vertexPath, const char *fragmentPath) {
    shader->name = name;

    this->oglApi->generateShaderIds(&(shader->vertexShader), &(shader->fragmentShader), &(shader->shaderProgram));
    this->oglApi->compileShaders(&(shader->vertexShader), vertexPath, &(shader->fragmentShader), fragmentPath);

    std::string vertexLogs = this->oglApi->checkCompilingStatusLog(shader->vertexShader);
    if(!vertexLogs.empty()) {
        this->sdlApi->errorLog(vertexLogs.c_str());
    }
    std::string fragmentLogs = this->oglApi->checkCompilingStatusLog(shader->fragmentShader);
    if(!fragmentLogs.empty()) {
        this->sdlApi->errorLog(fragmentLogs.c_str());
    }

    if(this->oglApi->attachAndLinkShaderProgram(&(shader->vertexShader), &(shader->fragmentShader), &(shader->shaderProgram))) {
        this->sdlApi->errorLog("[ShaderFactoryOpenGL]: Error compiling %s ", shader->name.c_str());
    }

    std::string programLogs = this->oglApi->checkLinkingStatusLog(shader->shaderProgram);
    if(!programLogs.empty()) {
        this->sdlApi->errorLog(programLogs.c_str());
    }

    this->oglApi->useProgram(&(shader->shaderProgram));
    shader->findUniformVariables(this->oglApi);
    shader->findVertexAttributeVariables(this->oglApi);
}

void ShaderFactoryOpenGL::init(Configuration *configuration, ShaderManager *shaderManager) {
    std::string path = configuration->getPropertyAsString("shadersFolder");
    std::string message("[ShaderFactoryOpenGL] Loading: ");
    this->sdlApi->infoLog(message.append(path).c_str());
    this->sdlApi->infoLog("[ShaderFactoryOpenGL] [    Loading Simple Shader]");

    auto* colorShader = new ColorShader();
    auto* normalShader = new NormalShader();
    auto* textureShader = new TextureShader();
    auto* lightningShader = new LightningShader();
    auto* normalMappingShader = new NormalMappingShader();
    auto* parallaxMapping = new ParallaxMappingShader();

    createShader(colorShader, "color", (path + "/simple.vert").c_str(), (path + "/simple.frag").c_str());
    createShader(normalShader, "normals", (path + "/normal.vert").c_str(), (path + "/normal.frag").c_str());
    createShader(textureShader, "texture", (path + "/texture.vert").c_str(), (path + "/texture.frag").c_str());
    createShader(lightningShader, "lightning", (path + "/lightning.vert").c_str(), (path + "/lightning.frag").c_str());
    createShader(normalMappingShader, "normalMapping", (path + "/normalMapping.vert").c_str(), (path + "/normalMapping.frag").c_str());
    createShader(parallaxMapping, "parallaxMapping", (path + "/parallaxMapping.vert").c_str(), (path + "/parallaxMapping.frag").c_str());

    shaderManager->addShader(colorShader);
    shaderManager->addShader(normalShader);
    shaderManager->addShader(textureShader);
    shaderManager->addShader(lightningShader);
    shaderManager->addShader(normalMappingShader);
    shaderManager->addShader(parallaxMapping);

    this->oglApi->cleanProgram();
    this->sdlApi->infoLog("[ShaderFactoryOpenGL] [    Simple Shader Loaded]");
    this->sdlApi->infoLog("[ShaderFactoryOpenGL] Shaders loading complete");
}

void ShaderFactoryOpenGL::destroy() {

}
