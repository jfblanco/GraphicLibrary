#ifndef ENGINETEST_CORESYSTEM_H
#define ENGINETEST_CORESYSTEM_H

#include "../interfaces/includes/RenderingSystemMock.h"
#include "../interfaces/includes/InputSystemMock.h"
#include "../interfaces/includes/ShaderFactoryMock.h"
#include "../interfaces/includes/PropertiesManager.h"
#include "../interfaces/includes/ShaderManager.h"
#include "../entities/include/Configuration.h"
#include "ResourcesManager.h"

class CoreSystem {
private:
    RenderingSystem *renderSystem = new RenderingSystemMock();
    InputSystem *inputSystem  = new InputSystemMock();
    ResourcesManager *resourcesSystem  = new ResourcesManager();
    Configuration *configuration = new Configuration();
    ConfigurationSystem *propertiesSystem = new PropertiesManager();
    ShaderManager *shaderSystem;
    ShaderFactory *shaderFactory = new ShaderFactoryMock();

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

    ResourcesManager *getResourcesSystem();
    void setResourcesSystem(ResourcesManager *resourcesSystem);

    ShaderManager *getShaderSystem();
    void setShaderSystem(ShaderManager *shaderSystem);

    ShaderFactory *getShaderFactory();
    void setShaderFactory(ShaderFactory *shaderFactory);

    Configuration *getConfig();
};


#endif //ENGINETEST_CORESYSTEM_H
