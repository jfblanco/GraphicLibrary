//
// Created by Francisco Blanco on 12/28/2023.
//

#include "CloseEvent.h"

void CloseEvent::quitTimeEvent(SDL_Event event) {
    if(event.type == SDL_EVENT_QUIT) {
        exitLoop = SDL_TRUE;
    }
}

void CloseEvent::mouseMove(SDL_Event event) {
    SDL_Log("X: %f Y: %f", event.motion.x, event.motion.y);
}
