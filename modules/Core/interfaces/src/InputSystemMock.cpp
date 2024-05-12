#include "../includes/InputSystemMock.h"

void InputSystemMock::init() {
    this->startTime = SDL_GetTicks();
}

void InputSystemMock::destroy() {

}

Boolean InputSystemMock::getExitLoop() {
    this->currentTime = SDL_GetTicks();
    if(currentTime > startTime + 10000) {
        return TRUE;
    } else {
        return FALSE;
    }
}

void InputSystemMock::checkEventQueue() {

}