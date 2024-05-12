#ifndef ENGINETEST_SDLAPI_H
#define ENGINETEST_SDLAPI_H

#include <SDL2/SDL.h>

typedef struct SDL_Window EngineWindow;
typedef SDL_Event EngineEvent;
typedef SDL_GLContext Engine3DContext;

enum {
    UNSIGNED_INTEGER_MAX_8 = SDL_MAX_UINT8,
    UNSIGNED_INTEGER_MIN_8 = SDL_MIN_UINT8,
    UNSIGNED_INTEGER_MAX_16 = SDL_MAX_UINT16,
    UNSIGNED_INTEGER_MIN_16 = SDL_MIN_UINT16,
    UNSIGNED_INTEGER_MAX_32 = SDL_MAX_UINT32,
    INTEGER_MAX_32 = SDL_MAX_SINT32,
    UNSIGNED_INTEGER_MIN_32 = SDL_MIN_UINT32,
    INTEGER_MIN_32 = SDL_MIN_SINT32,
    UNSIGNED_INTEGER_MAX_64 = SDL_MAX_UINT64,
    UNSIGNED_INTEGER_MIN_64 = SDL_MIN_UINT64
};

typedef enum
{
    TRUE = SDL_TRUE,
    FALSE = SDL_FALSE
} Boolean;

enum {
    QUIT_EVENT = SDL_QUIT,
    MOUSE_MOTION = SDL_MOUSEMOTION,
    MOUSE_BUTTON_DOWN = SDL_MOUSEBUTTONDOWN,
    MOUSE_BUTTON_UP = SDL_MOUSEBUTTONUP,
    MOUSE_WHEEL = SDL_MOUSEWHEEL,
    KEY_PRESSED = SDL_KEYDOWN,
    KEY_Z = SDLK_z,
    KEY_X = SDLK_x,
    KEY_D = SDLK_d,
    KEY_A = SDLK_a,
    KEY_W = SDLK_w,
    KEY_S = SDLK_s,
    KEY_K = SDLK_k,
    KEY_RIGHT = SDLK_RIGHT,
    KEY_LEFT = SDLK_LEFT,
    KEY_UP = SDLK_UP,
    KEY_DOWN = SDLK_DOWN,
    MOUSE_BUTTON_LEFT = SDL_BUTTON_LEFT,
    MOUSE_BUTTON_MIDDLE = SDL_BUTTON_MIDDLE,
    MOUSE_BUTTON_RIGHT = SDL_BUTTON_RIGHT,
    MOUSE_BUTTON_X1 = SDL_BUTTON_X1,
    MOUSE_BUTTON_X2 = SDL_BUTTON_X2,
};

typedef Sint8 Integer8;
typedef Sint16 Integer16;
typedef Sint32 Integer32;
typedef Sint64 Integer64;

typedef Uint8 UnsignedInteger8;
typedef Uint16 UnsignedInteger16;
typedef Uint32 UnsignedInteger32;
typedef Uint64 UnsignedInteger64;

class SDLAPI {
public:
    SDLAPI() = default;
    ~SDLAPI() = default;

    void initSDL();
    void initInputSDL();

    Integer16 checkEvent(EngineEvent*);
    Integer32 getEventType(EngineEvent*);

    EngineWindow* createWindow(const char*,int,int);
    void destroy(EngineWindow*);
    void swap(EngineWindow*);
    void preset3DGraphicConstants();
    Engine3DContext create3DContext(EngineWindow* _window);


    void infoLog(const char *);
    void infoLog(const char *, const char *);
    void errorLog(const char*);
    void errorLog(const char*, const char*);
    void debugLog(const char*, ...);
};


#endif //ENGINETEST_SDLAPI_H
