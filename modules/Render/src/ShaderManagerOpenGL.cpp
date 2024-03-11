#include "../include/ShaderManagerOpenGL.h"
#include "ShaderOpenGL.h"
#include <map>
#include <string>

Shader* ShaderManagerOpenGL::findShader(const std::string& key) {
    auto result = this->shaders.find(key);
    if(result != this->shaders.end()){
        return  result->second;
    }
    return this->mockShader;
}

void ShaderManagerOpenGL::addShader(Shader* shader) {
    this->shaders.insert(std::pair<std::string, ShaderOpenGL*>(shader->name, (ShaderOpenGL*) shader));
};
