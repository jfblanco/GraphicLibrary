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
    if(isLeftMouseClicked && (cubeElements[selected] != nullptr)) {
        if(event.type == SDL_MOUSEMOTION) {
            cubeElements[selected]->setRotation(cubeElements[selected]->eulerAngles.x + (0.01 * event.motion.yrel),
                                                cubeElements[selected]->eulerAngles.y + (0.01 * event.motion.xrel),
                                                cubeElements[selected]->eulerAngles.z);
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
    if(event.key.keysym.sym == SDLK_z) {
        cubeElements[selected]->setPosition(cubeElements[selected]->position.x,cubeElements[selected]->position.y,cubeElements[selected]->position.z + 0.5);
    }
    if(event.key.keysym.sym == SDLK_x) {
        cubeElements[selected]->setPosition(cubeElements[selected]->position.x,cubeElements[selected]->position.y,cubeElements[selected]->position.z - 0.5);
    }
    if(event.key.keysym.sym == SDLK_d) {
        cubeElements[selected]->setPosition(cubeElements[selected]->position.x + 0.05,cubeElements[selected]->position.y,cubeElements[selected]->position.z);
    }
    if(event.key.keysym.sym == SDLK_a) {
        cubeElements[selected]->setPosition(cubeElements[selected]->position.x - 0.05,cubeElements[selected]->position.y,cubeElements[selected]->position.z);
    }
    if(event.key.keysym.sym == SDLK_w) {
        cubeElements[selected]->setPosition(cubeElements[selected]->position.x,cubeElements[selected]->position.y + 0.05,cubeElements[selected]->position.z);
    }
    if(event.key.keysym.sym == SDLK_s) {
        cubeElements[selected]->setPosition(cubeElements[selected]->position.x,cubeElements[selected]->position.y - 0.05,cubeElements[selected]->position.z);
    }
    if(event.key.keysym.sym == SDLK_RIGHT) {
        selected -= 1;
        if(selected < 0) {
            selected = cubeElements.size() - 1;
        }
    }
    if(event.key.keysym.sym == SDLK_LEFT) {
        selected += 1;
        if(selected >= cubeElements.size()) {
            selected = 0;
        }
    }
    if(event.key.keysym.sym == SDLK_UP) {
        if(this->shader != nullptr) {
            this->shader->heightScale -= 0.01;
        }
    }
    if(event.key.keysym.sym == SDLK_DOWN) {
        if(this->shader != nullptr) {
            this->shader->heightScale += 0.01;
        }
    }
//    this->camera->viewMatrix = glm::lookAt(this->camera->position,this->camera->point,this->camera->orientation);
}
