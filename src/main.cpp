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
#include <NormalMappingShader.h>
#include <ParallaxMappingShader.h>
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

    ambientLight->color = glm::vec4(1.0, 1.0, 1.0, 0.0);
    diffuseLight->color = glm::vec4(1.0, 1.0, 1.0, 1.0);
    diffuseLight->position = glm::vec3(0.0, 0.0, 5.0);
    specularLight->color = glm::vec4(1.0, 1.0, 1.0, 1.0);

    auto* ambientLight2 = new Light();
    auto* diffuseLight2 = new Light();
    auto* specularLight2 = new Light();

    ambientLight2->color = glm::vec4(0.24725, 0.1995, 0.0745, 1.0);
    diffuseLight2->color = glm::vec4(0.75164, 0.60648, 0.22648, 1.0);
    diffuseLight2->position = glm::vec3(0.0, 1.0, 0.5);
    specularLight2->color = glm::vec4(0.628281, 0.555802, 0.366065, 1.0);

    auto* lightShader = (ShaderOpenGL*) coreSystem->getShaderSystem()->findShader("lightning");
    ((LightningShader*) lightShader)->ambient = ambientLight2;
    ((LightningShader*) lightShader)->diffuse = diffuseLight2;
    ((LightningShader*) lightShader)->specular = specularLight2;

    auto* normalMapping = (ShaderOpenGL*) coreSystem->getShaderSystem()->findShader("normalMapping");
    ((NormalMappingShader*) normalMapping)->ambient = ambientLight;
    ((NormalMappingShader*) normalMapping)->diffuse = diffuseLight;
    ((NormalMappingShader*) normalMapping)->specular = specularLight;

    auto* parallaxMapping = (ShaderOpenGL*) coreSystem->getShaderSystem()->findShader("parallaxMapping");
    ((ParallaxMappingShader*) parallaxMapping)->ambient = ambientLight;
    ((ParallaxMappingShader*) parallaxMapping)->diffuse = diffuseLight;
    ((ParallaxMappingShader*) parallaxMapping)->specular = specularLight;

//    auto* cube = coreSystem->getResourcesSystem()->getRenderable("UltraSphere");
//    auto* cube = coreSystem->getResourcesSystem()->getRenderable("IceCube");
//    auto* cube = coreSystem->getResourcesSystem()->getRenderable("Pildora");
//    auto* cube = coreSystem->getResourcesSystem()->getRenderable("dpIluminado");
//    auto* cube = coreSystem->getResourcesSystem()->getRenderable("Suzanne");
//    auto* cube = coreSystem->getResourcesSystem()->getRenderable("BolaIluminada");
//    auto* cubeIluminado = coreSystem->getResourcesSystem()->getRenderable("UltraLisaIluminada");
//    auto* cubeIluminado = coreSystem->getResourcesSystem()->getRenderable("CubeIluminado");
//    cube->material = new Material("color", (ShaderOpenGL*) coreSystem->getShaderSystem()->findShader("color"));

//    auto* cube = coreSystem->getResourcesSystem()->getRenderable("PlaneParaBrick");
    auto* cube = coreSystem->getResourcesSystem()->getRenderable("SpherePara");
    cube->setPosition(0.0, 0.0, 0.0);
    auto* cubeRenderable = new RenderableOpenGL(cube);
    cubeRenderable->prepareMaterial(coreSystem->getShaderSystem());
    renderManager->renderableFactoryOpenGl->createRenderableBuffers(cubeRenderable);
    renderManager->renderables.push_back(cubeRenderable);
    closeEvent->cubeElements.push_back(cubeRenderable->renderable);

//    auto* cubeIluminado = coreSystem->getResourcesSystem()->getRenderable("CubeIluminado");
//    auto* cubeRenderableIluminado = new RenderableOpenGL(cubeIluminado);
//    cubeRenderableIluminado->prepareMaterial(coreSystem->getShaderSystem());
//    renderManager->renderableFactoryOpenGl->createRenderableBuffers(cubeRenderableIluminado);
//    renderManager->renderables.push_back(cubeRenderableIluminado);
//    closeEvent->cubeElements.push_back(cubeRenderableIluminado->renderable);
    closeEvent->shader = dynamic_cast<ParallaxMappingShader *>(parallaxMapping);

    coreSystem->startGame();
    return 0;
}
