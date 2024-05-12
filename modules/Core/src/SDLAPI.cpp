#include "../include/SDLAPI.h"

void SDLAPI::initSDL() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[ RendererOpenGL ] Error creating SDL_INIT_VIDEO %s", SDL_GetError());
    }
}

void SDLAPI::initInputSDL() {
    if(!SDL_WasInit(SDL_INIT_EVENTS)){
        if(SDL_InitSubSystem(SDL_INIT_EVENTS)) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error initializing SDL EVENTS: %s", SDL_GetError());
        }
    } else {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "SDL_INIT_EVENTS was already initialized...");
    }
}

Integer16 SDLAPI::checkEvent(EngineEvent* _event) {
    return SDL_PollEvent(_event);
}

Integer32 SDLAPI::getEventType(EngineEvent* _event) {
    return _event->type;
}

void SDLAPI::preset3DGraphicConstants() {
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 4 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 5 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE,    8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,  8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,   8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,  8);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 8);

    SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE,   8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE,  8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);
}

EngineWindow* SDLAPI::createWindow(const char* title, int width, int height) {
    return SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,width, height, SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);;
}

void SDLAPI::destroy(EngineWindow* _window) {
    SDL_DestroyWindow(_window);
}

void SDLAPI::swap(EngineWindow* _window) {
    SDL_GL_SwapWindow(_window);
}

Engine3DContext SDLAPI::create3DContext(EngineWindow* _window) {
    SDL_GLContext context = SDL_GL_CreateContext(_window);
    if(nullptr == context) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error SDL_GL_CreateContext: %s", SDL_GetError());
        exit(0);
    }
    SDL_GL_SetSwapInterval(1);
    return context;
}

void SDLAPI::infoLog(const char *_message) {
    SDL_Log(_message);
}

void SDLAPI::infoLog(const char *_message, const char *_string) {
    SDL_Log(_message, _string);
}

void SDLAPI::errorLog(const char *_message) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, _message);
}

void SDLAPI::errorLog(const char *_message, const char *_string) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, _message, _string);
}

void SDLAPI::debugLog(const char*, ...) {

}