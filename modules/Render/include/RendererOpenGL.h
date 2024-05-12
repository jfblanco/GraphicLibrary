#ifndef ENGINETEST_RENDEREROPENGL_H
#define ENGINETEST_RENDEREROPENGL_H

#include <glm/glm.hpp>
#include <RenderingSystem.h>
#include <Camera.h>
#include <vector>
#include <SDLAPI.h>
#include <OpenGLAPI.h>
#include "Renderable.h"
#include "RenderableFactoryOpenGL.h"

class RendererOpenGL : public RenderingSystem {
private:
    void logSystemInformation();
public:
    SDLAPI *sdlApi = nullptr;
    OpenGLAPI *openGlApi = nullptr;

    EngineWindow *window = nullptr;
    Camera* camera = new Camera();
    glm::mat4x4 projection = glm::mat4x4();
    Engine3DContext gl_context = nullptr;
    std::vector<Renderable*> renderables;
    std::vector<Renderable*> guiRenderables;
    RenderableFactoryOpenGL *renderableFactoryOpenGl = nullptr;

    explicit RendererOpenGL(SDLAPI*,OpenGLAPI*,RenderableFactoryOpenGL*);
    ~RendererOpenGL() = default;

    void init() override;
    void destroy() override;
    void render() override;
    void cleanScreen() override;
};


#endif //ENGINETEST_RENDEREROPENGL_H
