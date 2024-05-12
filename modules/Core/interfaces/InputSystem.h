#ifndef ENGINETEST_INPUTSYSTEM_H
#define ENGINETEST_INPUTSYSTEM_H

#include <SDLAPI.h>

class InputSystem {
public:
    virtual void init()=0;
    virtual void destroy()=0;

    virtual Boolean getExitLoop()=0;
    virtual void checkEventQueue()=0;
};

#endif //ENGINETEST_INPUTSYSTEM_H
