#include "../modules/Core/Core.hpp"
#include "../modules/Render/include/ShaderFactoryOpenGL.h"
#include "events/CloseEvent.h"
#include <Material.h>
#include <EventManager.h>
#include <RendererOpenGL.h>
#include <ShaderManagerOpenGL.h>
#include <LightningShader.h>
#include <NormalMappingShader.h>
#include <ParallaxMappingShader.h>
#include <Light.h>
#include <GUIFactory.h>
#include <GUIManager.h>
#include <GUIEditorWindows.h>

#define BUFFER_OFFSET(a) ((void*)(a))

int main(int argc, char* argv[]) {
    auto* entity1 = new GameEntity();
    auto* closeEvent = new CloseEvent();
    auto* diskManager = new ResourcesManager();

    auto* sdlApi = new SDLAPI();
    auto* openGlApi = new OpenGLAPI();

    auto* eventManager = new EventManager(sdlApi);
    auto* renderableFactory = new RenderableFactoryOpenGL(openGlApi);
    auto* renderManager = new RendererOpenGL(sdlApi,openGlApi,renderableFactory);
    auto* shaderFactory = new ShaderFactoryOpenGL(sdlApi, openGlApi);

    auto* coreSystem = new CoreSystem();
    auto* shaderManager = new ShaderManagerOpenGL();
    auto* guiManager = new GUIManager();
    auto* guiFactory = new GUIFactory();
    auto* guiEditorWindows = new GUIEditorWindows();

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

    ambientLight->color = glm::vec4(0.0, 0.0, 0.0, 0.0);
    diffuseLight->color = glm::vec4(0.8, 0.8, 0.8, 1.0);
    diffuseLight->position = glm::vec3(0.0, 1.0, 6.0);
    specularLight->color = glm::vec4(1.0, 1.0, 1.0, 1.0);

    auto* ambientLight2 = new Light();
    auto* diffuseLight2 = new Light();
    auto* specularLight2 = new Light();

    ambientLight2->color = glm::vec4(0.24725, 0.1995, 0.0745, 1.0);
    diffuseLight2->color = glm::vec4(0.75164, 0.60648, 0.22648, 1.0);
    diffuseLight2->position = glm::vec3(0.0, 1.0, 0.5);
    specularLight2->color = glm::vec4(1.0, 1.0, 1.0, 1.0);

    auto* lightShader = coreSystem->getShaderSystem()->findShader("lightning");
    ((LightningShader*) lightShader)->ambient = ambientLight2;
    ((LightningShader*) lightShader)->diffuse = diffuseLight2;
    ((LightningShader*) lightShader)->specular = specularLight2;

    auto* normalMapping = coreSystem->getShaderSystem()->findShader("normalMapping");
    ((NormalMappingShader*) normalMapping)->ambient = ambientLight;
    ((NormalMappingShader*) normalMapping)->diffuse = diffuseLight;
    ((NormalMappingShader*) normalMapping)->specular = specularLight;

    auto* parallaxMapping = coreSystem->getShaderSystem()->findShader("parallaxMapping");
    ((ParallaxMappingShader*) parallaxMapping)->ambient = ambientLight;
    ((ParallaxMappingShader*) parallaxMapping)->diffuse = diffuseLight;
    ((ParallaxMappingShader*) parallaxMapping)->specular = specularLight;

//    auto* cube = coreSystem->getResourcesSystem()->getRenderable("SuperPolySphere");
//    auto* cube = coreSystem->getResourcesSystem()->getRenderable("IceCube");
//    auto* cube = coreSystem->getResourcesSystem()->getRenderable("Pildora");
//    auto* cube = coreSystem->getResourcesSystem()->getRenderable("dpIluminado");
//    auto* cube = coreSystem->getResourcesSystem()->getRenderable("Suzanne");
//    auto* cube = coreSystem->getResourcesSystem()->getRenderable("BolaIluminada");
//    auto* cubeIluminado = coreSystem->getResourcesSystem()->getRenderable("UltraLisaIluminada");
//    auto* cubeIluminado = coreSystem->getResourcesSystem()->getRenderable("CubeIluminado");
//    cube->material = new Material("color", (ShaderOpenGL*) coreSystem->getShaderSystem()->findShader("color"));

    auto* cube = coreSystem->getResourcesSystem()->getRenderable("PlanePara");
//    auto* cube = coreSystem->getResourcesSystem()->getRenderable("PlaneTestPara");
//    auto* cube = coreSystem->getResourcesSystem()->getRenderable("PlaneParaBrick");
//    auto* cube = coreSystem->getResourcesSystem()->getRenderable("PlaneSillon");
//    auto* cube = coreSystem->getResourcesSystem()->getRenderable("SpherePara");
    cube->setPosition(0.0, 1.0, 2.0);
    cube->setRotation(1.33, 0.0, 0.0);
    cube->prepareMaterial(coreSystem->getShaderSystem());
    renderManager->renderableFactoryOpenGl->createRenderableBuffers(cube);
    renderManager->renderables.push_back(cube);
    closeEvent->cubeElements.push_back(cube);
    closeEvent->shader = dynamic_cast<ParallaxMappingShader *>(parallaxMapping);

//    auto* cubeIluminado = coreSystem->getResourcesSystem()->getRenderable("CubeIluminado");
//    cubeIluminado->prepareMaterial(coreSystem->getShaderSystem());
//    renderManager->renderableFactoryOpenGl->createRenderableBuffers(cubeIluminado);
//    renderManager->renderables.push_back(cubeIluminado);
//    closeEvent->cubeElements.push_back(cubeIluminado);

    guiFactory->createMainWindow(guiEditorWindows);
//    renderManager->

    coreSystem->startGame();
    return 0;
}
