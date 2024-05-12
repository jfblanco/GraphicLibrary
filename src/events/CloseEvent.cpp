#include "CloseEvent.h"
#include <Camera.h>
#include <Renderable.h>

void CloseEvent::quitTimeEvent(EngineEvent event) {
    if(event.type == QUIT_EVENT) {
        exitLoop = TRUE;
    }
}

void CloseEvent::mouseMove(EngineEvent event) {
    if(isLeftMouseClicked && (cubeElements[selected] != nullptr)) {
        if(event.type == MOUSE_MOTION) {
            cubeElements[selected]->setRotation(cubeElements[selected]->eulerAngles.x + (0.01 * event.motion.yrel),
                                                cubeElements[selected]->eulerAngles.y + (0.01 * event.motion.xrel),
                                                cubeElements[selected]->eulerAngles.z);
        }
    }
}

void CloseEvent::mouseButtonPressed(EngineEvent event) {
    if(event.button.button == MOUSE_BUTTON_LEFT) {
        this->isLeftMouseClicked = TRUE;
    }
}

void CloseEvent::mouseButtonReleased(EngineEvent event) {
    if(event.button.button == MOUSE_BUTTON_LEFT) {
        this->isLeftMouseClicked = FALSE;
    }
}

void CloseEvent::keyDownTimeEvent(EngineEvent event) {
    if(event.key.keysym.sym == KEY_Z) {
        cubeElements[selected]->setPosition(cubeElements[selected]->position.x,cubeElements[selected]->position.y,cubeElements[selected]->position.z + 0.5);
    }
    if(event.key.keysym.sym == KEY_X) {
        cubeElements[selected]->setPosition(cubeElements[selected]->position.x,cubeElements[selected]->position.y,cubeElements[selected]->position.z - 0.5);
    }
    if(event.key.keysym.sym == KEY_D) {
        cubeElements[selected]->setPosition(cubeElements[selected]->position.x + 0.05,cubeElements[selected]->position.y,cubeElements[selected]->position.z);
    }
    if(event.key.keysym.sym == KEY_A) {
        cubeElements[selected]->setPosition(cubeElements[selected]->position.x - 0.05,cubeElements[selected]->position.y,cubeElements[selected]->position.z);
    }
    if(event.key.keysym.sym == KEY_W) {
        cubeElements[selected]->setPosition(cubeElements[selected]->position.x,cubeElements[selected]->position.y + 0.05,cubeElements[selected]->position.z);
    }
    if(event.key.keysym.sym == KEY_S) {
        cubeElements[selected]->setPosition(cubeElements[selected]->position.x,cubeElements[selected]->position.y - 0.05,cubeElements[selected]->position.z);
    }
    if(event.key.keysym.sym == KEY_RIGHT) {
        selected -= 1;
        if(selected < 0) {
            selected = cubeElements.size() - 1;
        }
    }
    if(event.key.keysym.sym == KEY_LEFT) {
        selected += 1;
        if(selected >= cubeElements.size()) {
            selected = 0;
        }
    }
    if(event.key.keysym.sym == KEY_UP) {
        if(this->shader != nullptr) {
            this->shader->heightScale -= 0.01;
        }
    }
    if(event.key.keysym.sym == KEY_DOWN) {
        if(this->shader != nullptr) {
            this->shader->heightScale += 0.01;
        }
    }
//    this->camera->viewMatrix = glm::lookAt(this->camera->position,this->camera->point,this->camera->orientation);
}
