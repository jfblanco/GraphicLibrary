#ifndef ENGINETEST_INPUTSYSTEM_H
#define ENGINETEST_INPUTSYSTEM_H

#include "SDL3/SDL.h"

class InputSystem {
public:
    virtual void init()=0;
    virtual void destroy()=0;

    virtual SDL_bool getExitLoop()=0;
    virtual void checkEventQueue()=0;
};

#endif //ENGINETEST_INPUTSYSTEM_H
