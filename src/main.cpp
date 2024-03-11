#include <SDL2/SDL.h>
#include <SDL2_image/include/SDL2/SDL_image.h>

#include "../modules/Core/Core.hpp"
#include "../modules/Render/include/ShaderFactoryOpenGL.h"
#include "events/CloseEvent.h"
#include <Material.h>
#include <EventManager.h>
#include <RendererOpenGL.h>
#include <ShaderManagerOpenGL.h>
#include <iostream>

typedef struct {
    GLenum       type;
    const char*  filename;
    GLuint       shader;
} ShaderInfo;

static const GLchar*
ReadShader( const char* filename )
{
    #ifdef WIN32
        FILE* infile;
        fopen_s( &infile, filename, "rb" );
    #else
        FILE* infile = fopen( filename, "rb" );
    #endif // WIN32

        if ( !infile ) {
    #ifdef _DEBUG
            std::cerr << "Unable to open file '" << filename << "'" << std::endl;
    #endif /* DEBUG */
            return NULL;
        }

        fseek( infile, 0, SEEK_END );
        int len = ftell( infile );
        fseek( infile, 0, SEEK_SET );

        GLchar* source = new GLchar[len+1];

        fread( source, 1, len, infile );
        fclose( infile );

        source[len] = 0;

        return const_cast<const GLchar*>(source);
}

GLint LoadShaders(ShaderInfo* shaders) {

    if ( shaders == NULL ) { return 0; }

    GLuint program = glCreateProgram();

    ShaderInfo* entry = shaders;
    while ( entry->type != GL_NONE ) {
        GLuint shader = glCreateShader( entry->type );

        entry->shader = shader;

        const GLchar* source = ReadShader( entry->filename );
        if ( source == NULL ) {
            for ( entry = shaders; entry->type != GL_NONE; ++entry ) {
                glDeleteShader( entry->shader );
                entry->shader = 0;
            }

            return 0;
        }

        glShaderSource( shader, 1, &source, NULL );
        delete [] source;

        glCompileShader( shader );

        GLint compiled;
        glGetShaderiv( shader, GL_COMPILE_STATUS, &compiled );
        if ( !compiled ) {
        #ifdef _DEBUG
        GLsizei len;
        glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &len );

        GLchar* log = new GLchar[len+1];
        glGetShaderInfoLog( shader, len, &len, log );
        std::cerr << "Shader compilation failed: " << log << std::endl;
        delete [] log;
        #endif /* DEBUG */

        return 0;
        }

        glAttachShader( program, shader );

        ++entry;
    }

    glLinkProgram( program );

    GLint linked;
    glGetProgramiv( program, GL_LINK_STATUS, &linked );
    if ( !linked ) {
    #ifdef _DEBUG
    GLsizei len;
    glGetProgramiv( program, GL_INFO_LOG_LENGTH, &len );

    GLchar* log = new GLchar[len+1];
    glGetProgramInfoLog( program, len, &len, log );
    std::cerr << "Shader linking failed: " << log << std::endl;
    delete [] log;
    #endif /* DEBUG */

    for ( entry = shaders; entry->type != GL_NONE; ++entry ) {
        glDeleteShader( entry->shader );
        entry->shader = 0;
    }

    return 0;
    }

    return program;
}

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
//    eventManager->addMouseEventListener(closeEvent);

    if(!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL Image could not be initialized! Error: %s", SDL_GetError());
    }

    Uint16 algo = coreSystem->getConfig()->getPropertyAsUInt16("algo");
    auto* cube = coreSystem->getResourcesSystem()->getRenderable("Ball");
    cube->material = new Material("color", (ShaderOpenGL*) coreSystem->getShaderSystem()->findShader("color"));

    auto* cubeRenderable = new RenderableOpenGL(cube);
    renderManager->renderableFactoryOpenGl->createRenderableBuffers(cubeRenderable);
    renderManager->renderables.push_back(cubeRenderable);

    coreSystem->startGame();
    return 0;
}
