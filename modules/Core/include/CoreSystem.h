//
// Created by Francisco Blanco on 2/24/2024.
//

#ifndef ENGINETEST_CORESYSTEM_H
#define ENGINETEST_CORESYSTEM_H

#include "../interfaces/includes/RenderingSystemMock.h"
#include "../interfaces/includes/InputSystemMock.h"
#include "../interfaces/includes/PropertiesManager.h"
#include "../entities/include/Configuration.h"

class CoreSystem {
private:
    RenderingSystem *renderSystem = new RenderingSystemMock();
    InputSystem *inputSystem  = new InputSystemMock();
    Configuration *configuration = new Configuration();
    ConfigurationSystem *propertiesSystem = new PropertiesManager();
public:
    CoreSystem() = default;
    ~CoreSystem() = default;

    void init();
    void startGame();
    void destroy();

    RenderingSystem *getRenderSystem();
    void setRenderSystem(RenderingSystem *renderingSystem);

    InputSystem *getInputSystem();
    void setInputSystem(InputSystem *inputSystem);

    Configuration *getConfig();
};


#endif //ENGINETEST_CORESYSTEM_H
