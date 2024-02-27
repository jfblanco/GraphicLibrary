#include "../include/CoreSystem.h"

void CoreSystem::startGame() {
    while (!inputSystem->getExitLoop()) {
        inputSystem->checkEventQueue();
        this->renderSystem->cleanScreen();
        this->renderSystem->render();
    }
    SDL_Quit();
}

void CoreSystem::init() {
    this->propertiesSystem->init(this->configuration);
    this->inputSystem->init();
    this->renderSystem->init();
}

void CoreSystem::destroy() {
    this->renderSystem->destroy();
    this->inputSystem->destroy();
}

RenderingSystem* CoreSystem::getRenderSystem() {
    return this->renderSystem;
}

void CoreSystem::setRenderSystem(RenderingSystem *renderingSystem) {
    this->renderSystem = renderingSystem;
}

InputSystem* CoreSystem::getInputSystem() {
    return this->inputSystem;
}

void CoreSystem::setInputSystem(InputSystem *inputSystem){
    this->inputSystem = inputSystem;
}

Configuration* CoreSystem::getConfig() {
    return this->configuration;
}
