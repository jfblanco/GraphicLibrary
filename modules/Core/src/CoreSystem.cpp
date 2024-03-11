#include "../include/CoreSystem.h"

void CoreSystem::startGame() {
    while (!inputSystem->getExitLoop()) {
        inputSystem->checkEventQueue();
        this->renderSystem->render();
        this->renderSystem->cleanScreen();
    }
    SDL_Quit();
}

void CoreSystem::init() {
//    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
//        SDL_Log("Couldn't initialize SDL: %s\n",SDL_GetError());
//        exit(255);
//    }

    this->propertiesSystem->init(this->configuration);
    this->inputSystem->init();
    this->renderSystem->init();
    this->resourcesSystem->init(this->configuration);
    this->resourcesSystem->load3DModels();
    this->shaderFactory->init(this->configuration, this->shaderSystem);
}

void CoreSystem::destroy() {
    this->renderSystem->destroy();
    this->inputSystem->destroy();
}

RenderingSystem* CoreSystem::getRenderSystem() {
    return this->renderSystem;
}

void CoreSystem::setRenderSystem(RenderingSystem *_renderingSystem) {
    this->renderSystem = _renderingSystem;
}

InputSystem* CoreSystem::getInputSystem() {
    return this->inputSystem;
}

void CoreSystem::setInputSystem(InputSystem *_inputSystem){
    this->inputSystem = _inputSystem;
}

ResourcesManager* CoreSystem::getResourcesSystem() {
    return this->resourcesSystem;
}

void CoreSystem::setResourcesSystem(ResourcesManager *_resourcesSystem){
    this->resourcesSystem = _resourcesSystem;
}

Configuration* CoreSystem::getConfig() {
    return this->configuration;
}

ShaderManager* CoreSystem::getShaderSystem() {
    return this->shaderSystem;
}

void CoreSystem::setShaderSystem(ShaderManager *_shaderSystem) {
    this->shaderSystem = _shaderSystem;
}

ShaderFactory* CoreSystem::getShaderFactory() {
    return this->shaderFactory;
}

void CoreSystem::setShaderFactory(ShaderFactory *_shaderFactory) {
    this->shaderFactory = _shaderFactory;

}
