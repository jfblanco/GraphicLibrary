#include "CloseEvent.h"
#include <SDL2/SDL.h>
#include <Camera.h>
#include <Renderable.h>
#include <glm/ext/matrix_transform.hpp>

void CloseEvent::quitTimeEvent(SDL_Event event) {
    if(event.type == SDL_QUIT) {
        exitLoop = SDL_TRUE;
    }
}

void CloseEvent::mouseMove(SDL_Event event) {
    if(isLeftMouseClicked && (cubeElement != nullptr)) {
        if(event.type == SDL_MOUSEMOTION) {
            cubeElement->setRotation(cubeElement->eulerAngles.x + (0.01 * event.motion.yrel),
                                     cubeElement->eulerAngles.y + (0.01 * event.motion.xrel),
                                     cubeElement->eulerAngles.z);
        }
    }
}

void CloseEvent::mouseButtonPressed(SDL_Event event) {
    if(event.button.button == SDL_BUTTON_LEFT) {
        this->isLeftMouseClicked = SDL_TRUE;
    }
}

void CloseEvent::mouseButtonReleased(SDL_Event event) {
    if(event.button.button == SDL_BUTTON_LEFT) {
        this->isLeftMouseClicked = SDL_FALSE;
    }
}

void CloseEvent::keyDownTimeEvent(SDL_Event event) {
    if(event.key.keysym.sym == SDLK_w) {
        this->camera->position.y += 0.2;
        this->camera->point.y += 0.2;
    }
    if(event.key.keysym.sym == SDLK_s) {
        this->camera->position.y -= 0.2;
        this->camera->point.y -= 0.2;
    }
    if(event.key.keysym.sym == SDLK_d) {
        this->camera->position.x += 0.2;
        this->camera->point.x += 0.2;
    }
    if(event.key.keysym.sym == SDLK_a) {
        this->camera->position.x -= 0.2;
        this->camera->point.x -= 0.2;
    }
    this->camera->viewMatrix = glm::lookAt(this->camera->position,this->camera->point,this->camera->orientation);
}
