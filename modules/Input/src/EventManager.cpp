#include "../include/EventManager.h"
#include "../include/EventListener.h"

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
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Initializing [EventManager]");
    if(!SDL_WasInit(SDL_INIT_EVENTS)){
        if(SDL_InitSubSystem(SDL_INIT_EVENTS)) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error initializing SDL EVENTS: %s", SDL_GetError());
        }
    } else {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "SDL_INIT_EVENTS was already initialized...");
    }
    this->quitEventListeners.resize(this->quitEventBufferSize);
    this->keyBoardEventListeners.resize(this->keyBoardEventBufferSize);
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "[EventManager] Init Completed");
}

void EventManager::checkEventQueue() {
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT:
                this->sendQuitEventToAllListeners();
                break;
            case SDL_EVENT_KEY_DOWN:
                this->sendKeyboardEventToAllListeners();
                break;
            case SDL_EVENT_MOUSE_MOTION:
                this->sendMouseEventToAllListeners();
                break;
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                this->sendMouseEventToAllListeners();
                break;
            case SDL_EVENT_MOUSE_BUTTON_UP:
                this->sendMouseEventToAllListeners();
                break;
            case SDL_EVENT_MOUSE_WHEEL:
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
            if(this->event.type == SDL_EVENT_MOUSE_WHEEL){
                item->mouseScroll(this->event);
            }
            if(this->event.type == SDL_EVENT_MOUSE_MOTION){
                item->mouseMove(this->event);
            }
            if(this->event.type == SDL_EVENT_MOUSE_BUTTON_DOWN){
                item->mouseButtonPressed(this->event);
            }
            if(this->event.type == SDL_EVENT_MOUSE_BUTTON_UP){
                item->mouseButtonReleased(this->event);
            }
        }
    }
}

