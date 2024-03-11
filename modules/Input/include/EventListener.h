#ifndef GAMEENGINE_EVENTLISTENER_H
#define GAMEENGINE_EVENTLISTENER_H

#include <SDL2/SDL.h>

class EventListener {
public:
    EventListener() = default;
    ~EventListener() = default;
    virtual void quitTimeEvent(SDL_Event) = 0;
    virtual void keyDownTimeEvent(SDL_Event) = 0;
    virtual void mouseButtonPressed(SDL_Event) = 0;
    virtual void mouseButtonReleased(SDL_Event) = 0;
    virtual void mouseScroll(SDL_Event) = 0;
    virtual void mouseMove(SDL_Event) = 0;
};

#endif //GAMEENGINE_EVENTLISTENER_H

