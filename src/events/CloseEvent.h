#ifndef ENGINETEST_CLOSEEVENT_H
#define ENGINETEST_CLOSEEVENT_H

#include <EventListener.h>
#include <ParallaxMappingShader.h>
#include <vector>

class Camera;
class Renderable;
class CloseEvent : public EventListener {
private:
    Boolean exitLoop = FALSE;
public:
    CloseEvent()=default;
    ~CloseEvent()=default;

    Camera* camera;
    ParallaxMappingShader* shader = nullptr;
    Integer8 selected = 0;
    std::vector<Renderable*> cubeElements;
    Boolean isLeftMouseClicked = FALSE;

    Boolean getExitLoop() { return this->exitLoop; };
    void quitTimeEvent(EngineEvent) override;
    void keyDownTimeEvent(EngineEvent) override;
    void mouseButtonPressed(EngineEvent) override;
    void mouseButtonReleased(EngineEvent) override;
    void mouseScroll(EngineEvent) override {};
    void mouseMove(EngineEvent) override;
};

#endif //ENGINETEST_CLOSEEVENT_H
