#ifndef ENGINETEST_RENDERINGSYSTEM_H
#define ENGINETEST_RENDERINGSYSTEM_H

class RenderingSystem {
public:
    virtual void init()=0;
    virtual void destroy()=0;
    virtual void render()=0;
    virtual void cleanScreen()=0;
};


#endif //ENGINETEST_RENDERINGSYSTEM_H
