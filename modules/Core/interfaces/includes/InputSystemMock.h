#ifndef ENGINETEST_INPUTSYSTEMMOCK_H
#define ENGINETEST_INPUTSYSTEMMOCK_H

#include "../InputSystem.h"

class InputSystemMock : public InputSystem {
private:
    Uint64 startTime = SDL_MIN_UINT64;
    Uint64 currentTime = SDL_MIN_UINT64;
public:
    void init() override;
    void destroy() override;

    Boolean getExitLoop() override;
    void checkEventQueue() override;

    InputSystemMock() = default;
    ~InputSystemMock() = default;
};


#endif //ENGINETEST_INPUTSYSTEMMOCK_H
