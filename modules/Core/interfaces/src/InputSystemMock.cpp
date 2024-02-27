#include "../includes/InputSystemMock.h"

void InputSystemMock::init() {
    this->startTime = SDL_GetTicks();
}

void InputSystemMock::destroy() {

}

SDL_bool InputSystemMock::getExitLoop() {
    this->currentTime = SDL_GetTicks();
    if(currentTime > startTime + 10000) {
        return SDL_TRUE;
    } else {
        return SDL_FALSE;
    }
}

void InputSystemMock::checkEventQueue() {

}