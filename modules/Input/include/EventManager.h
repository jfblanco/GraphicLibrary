#ifndef GAMEENGINE_EVENTMANAGER_H
#define GAMEENGINE_EVENTMANAGER_H

#include <SDLAPI.h>
#include <InputSystem.h>
#include <vector>

class EventListener;
class EventManager : public InputSystem {
    private:
        SDLAPI *sdlApi = nullptr;
        EngineEvent event{};
        UnsignedInteger8 quitEventBufferSize = 0;
        UnsignedInteger8 keyBoardEventBufferSize = 0;
        UnsignedInteger8 mouseEventBufferSize = 0;
        Boolean exitLoop = FALSE;

        std::vector<EventListener*> quitEventListeners;
        std::vector<EventListener*> keyBoardEventListeners;
        std::vector<EventListener*> mouseEventListeners;

        void sendQuitEventToAllListeners();
        void sendKeyboardEventToAllListeners();
        void sendMouseEventToAllListeners();

    public:
        explicit EventManager(SDLAPI *_sdlApi) { sdlApi = _sdlApi; };
        ~EventManager() = default;

        void init() override;
        void destroy() override;
        void checkEventQueue() override;
        Boolean getExitLoop() override;
        void addQuitEventListener(EventListener*);
        void addKeyBoardEventListener(EventListener*);
        void addMouseEventListener(EventListener*);
};


#endif //GAMEENGINE_EVENTMANAGER_H

