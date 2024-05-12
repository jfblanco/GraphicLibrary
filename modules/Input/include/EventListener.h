#ifndef GAMEENGINE_EVENTLISTENER_H
#define GAMEENGINE_EVENTLISTENER_H

#include <SDLAPI.h>

class EventListener {
public:
    EventListener() = default;
    ~EventListener() = default;
    virtual void quitTimeEvent(EngineEvent) = 0;
    virtual void keyDownTimeEvent(EngineEvent) = 0;
    virtual void mouseButtonPressed(EngineEvent) = 0;
    virtual void mouseButtonReleased(EngineEvent) = 0;
    virtual void mouseScroll(EngineEvent) = 0;
    virtual void mouseMove(EngineEvent) = 0;
};

#endif //GAMEENGINE_EVENTLISTENER_H

