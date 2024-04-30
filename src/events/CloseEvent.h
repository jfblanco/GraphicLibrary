#ifndef ENGINETEST_CLOSEEVENT_H
#define ENGINETEST_CLOSEEVENT_H

#include <EventListener.h>
#include <ParallaxMappingShader.h>
#include <vector>

class Camera;
class Renderable;
class CloseEvent : public EventListener {
private:
    SDL_bool exitLoop = SDL_FALSE;
public:
    CloseEvent()=default;
    ~CloseEvent()=default;

    Camera* camera;
    ParallaxMappingShader* shader = nullptr;
    Sint8 selected = 0;
    std::vector<Renderable*> cubeElements;
    SDL_bool isLeftMouseClicked = SDL_FALSE;

    SDL_bool getExitLoop() { return this->exitLoop; };
    void quitTimeEvent(SDL_Event) override;
    void keyDownTimeEvent(SDL_Event) override;
    void mouseButtonPressed(SDL_Event) override;
    void mouseButtonReleased(SDL_Event) override;
    void mouseScroll(SDL_Event) override {};
    void mouseMove(SDL_Event) override;
};


#endif //ENGINETEST_CLOSEEVENT_H
