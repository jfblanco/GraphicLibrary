#ifndef GAMEENGINE_EVENTMANAGER_H
#define GAMEENGINE_EVENTMANAGER_H

#include <SDL3/SDL.h>
#include <InputSystem.h>
#include <vector>

class EventListener;
class EventManager : public InputSystem {
    private:
        SDL_Event event{};
        Uint8 quitEventBufferSize = 0;
        Uint8 keyBoardEventBufferSize = 0;
        Uint8 mouseEventBufferSize = 0;
        SDL_bool exitLoop = SDL_FALSE;

        std::vector<EventListener*> quitEventListeners;
        std::vector<EventListener*> keyBoardEventListeners;
        std::vector<EventListener*> mouseEventListeners;

        void sendQuitEventToAllListeners();
        void sendKeyboardEventToAllListeners();
        void sendMouseEventToAllListeners();

    public:
        EventManager() = default;
        ~EventManager() = default;

        void init() override;
        void destroy() override;
        void checkEventQueue() override;
        SDL_bool getExitLoop() override;
        void addQuitEventListener(EventListener*);
        void addKeyBoardEventListener(EventListener*);
        void addMouseEventListener(EventListener*);
};


#endif //GAMEENGINE_EVENTMANAGER_H

