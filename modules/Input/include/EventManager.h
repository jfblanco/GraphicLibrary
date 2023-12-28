#ifndef GAMEENGINE_EVENTMANAGER_H
#define GAMEENGINE_EVENTMANAGER_H

#include <SDL3/SDL.h>
#include <vector>

class EventListener;
class EventManager {
    private:
        SDL_Event event{};
        Uint8 quitEventBufferSize = 0;
        Uint8 keyBoardEventBufferSize = 0;
        Uint8 mouseEventBufferSize = 0;

        std::vector<EventListener*> quitEventListeners;
        std::vector<EventListener*> keyBoardEventListeners;
        std::vector<EventListener*> mouseEventListeners;

        void sendQuitEventToAllListeners();
        void sendKeyboardEventToAllListeners();
        void sendMouseEventToAllListeners();

    public:
        EventManager() = default;
        ~EventManager() = default;

        void init();
        void checkEventQueue();
        void addQuitEventListener(EventListener*);
        void addKeyBoardEventListener(EventListener*);
        void addMouseEventListener(EventListener*);
};


#endif //GAMEENGINE_EVENTMANAGER_H

