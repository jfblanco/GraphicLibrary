#include <EventManager.h>
#include <EventListener.h>

void EventManager::addQuitEventListener(EventListener* quitEventListener) {
    this->quitEventListeners.push_back(quitEventListener);
}

void EventManager::addKeyBoardEventListener(EventListener* quitEventListener) {
    this->keyBoardEventListeners.push_back(quitEventListener);
}

void EventManager::addMouseEventListener(EventListener* quitEventListener) {
    this->mouseEventListeners.push_back(quitEventListener);
}

void EventManager::sendQuitEventToAllListeners() {
    for (EventListener* item : this->quitEventListeners) {
        if(item != nullptr) {
            item->quitTimeEvent(this->event);
        }
    }
}

void EventManager::init() {
    this->sdlApi->infoLog("Initializing [EventManager]");
    this->sdlApi->initInputSDL();
    this->quitEventListeners.resize(this->quitEventBufferSize);
    this->keyBoardEventListeners.resize(this->keyBoardEventBufferSize);
    this->sdlApi->infoLog("[EventManager] Init Completed");
}

void EventManager::destroy() {

}

Boolean EventManager::getExitLoop() {
    return this->exitLoop;
}

void EventManager::checkEventQueue() {
    while (this->sdlApi->checkEvent(&event)) {
        switch (this->sdlApi->getEventType(&event)) {
            case QUIT_EVENT:
                this->exitLoop = TRUE;
                this->sendQuitEventToAllListeners();
                break;
            case KEY_PRESSED:
                this->sendKeyboardEventToAllListeners();
                break;
            case MOUSE_MOTION:
                this->sendMouseEventToAllListeners();
                break;
            case MOUSE_BUTTON_DOWN:
                this->sendMouseEventToAllListeners();
                break;
            case MOUSE_BUTTON_UP:
                this->sendMouseEventToAllListeners();
                break;
            case MOUSE_WHEEL:
                this->sendMouseEventToAllListeners();
                break;
        }
    }
}

void EventManager::sendKeyboardEventToAllListeners() {
    for (EventListener* item : this->keyBoardEventListeners) {
        if(item != nullptr) {
            item->keyDownTimeEvent(this->event);
        }
    }
}

void EventManager::sendMouseEventToAllListeners() {
    for (EventListener* item : this->mouseEventListeners) {
        if(item != nullptr) {
            if(this->event.type == MOUSE_WHEEL){
                item->mouseScroll(this->event);
            }
            if(this->event.type == MOUSE_MOTION){
                item->mouseMove(this->event);
            }
            if(this->event.type == MOUSE_BUTTON_DOWN){
                item->mouseButtonPressed(this->event);
            }
            if(this->event.type == MOUSE_BUTTON_UP){
                item->mouseButtonReleased(this->event);
            }
        }
    }
}

