#include <SDL2/SDL.h>
#include <SDL2_image/include/SDL2/SDL_image.h>

#include "../modules/Core/Core.hpp"
#include "../modules/Render/include/ShaderFactoryOpenGL.h"
#include "events/CloseEvent.h"
#include <MaterialOpenGL.h>
#include <EventManager.h>
#include <RendererOpenGL.h>
#include <ShaderManagerOpenGL.h>
#include <LightningShader.h>
#include <Light.h>
#include <glm/glm.hpp>

#define BUFFER_OFFSET(a) ((void*)(a))

int main(int argc, char* argv[]) {
    auto* entity1 = new GameEntity();
    auto* closeEvent = new CloseEvent();
    auto* eventManager = new EventManager();
    auto* diskManager = new ResourcesManager();
    auto* renderManager = new RendererOpenGL();
    auto* coreSystem = new CoreSystem();
    auto* shaderFactory = new ShaderFactoryOpenGL();
    auto* shaderManager = new ShaderManagerOpenGL();

    coreSystem->setRenderSystem(renderManager);
    coreSystem->setInputSystem(eventManager);
    coreSystem->setShaderFactory(shaderFactory);
    coreSystem->setShaderSystem(shaderManager);
    coreSystem->init();

    closeEvent->camera = renderManager->camera;
    eventManager->addQuitEventListener(closeEvent);
    eventManager->addKeyBoardEventListener(closeEvent);
    eventManager->addMouseEventListener(closeEvent);

    auto* ambientLight = new Light();
    auto* diffuseLight = new Light();
    auto* specularLight = new Light();

    ambientLight->color = glm::vec4(1.0, 1.0, 1.0, 0.2);
    diffuseLight->color = glm::vec4(0.0, 0.0, 1.0, 1.0);
    diffuseLight->position = glm::vec3(0.0, 1.0, 0.5);
    specularLight->color = glm::vec4(1.0, 1.0, 1.0, 1.0);

    auto* lightShader = (ShaderOpenGL*) coreSystem->getShaderSystem()->findShader("lightning");
    ((LightningShader*) lightShader)->ambient = ambientLight;
    ((LightningShader*) lightShader)->diffuse = diffuseLight;
    ((LightningShader*) lightShader)->specular = specularLight;

//    auto* cube = coreSystem->getResourcesSystem()->getRenderable("UltraSphere");
//    auto* cube = coreSystem->getResourcesSystem()->getRenderable("IceCube");
//    auto* cube = coreSystem->getResourcesSystem()->getRenderable("Pildora");
//    auto* cube = coreSystem->getResourcesSystem()->getRenderable("dpIluminado");
//    auto* cube = coreSystem->getResourcesSystem()->getRenderable("Suzanne");
//    auto* cube = coreSystem->getResourcesSystem()->getRenderable("BolaIluminada");
//    auto* cube = coreSystem->getResourcesSystem()->getRenderable("UltraLisaIluminada");
    auto* cube = coreSystem->getResourcesSystem()->getRenderable("CubeIluminado");
//    auto* cube = coreSystem->getResourcesSystem()->getRenderable("IcosphereIluminada");

//    cube->material = new Material("color", (ShaderOpenGL*) coreSystem->getShaderSystem()->findShader("color"));
    auto* cubeRenderable = new RenderableOpenGL(cube);
    cubeRenderable->prepareMaterial(coreSystem->getShaderSystem());


    renderManager->renderableFactoryOpenGl->createRenderableBuffers(cubeRenderable);
    renderManager->renderables.push_back(cubeRenderable);
    closeEvent->cubeElement = cubeRenderable->renderable;

    coreSystem->startGame();
    return 0;
}
