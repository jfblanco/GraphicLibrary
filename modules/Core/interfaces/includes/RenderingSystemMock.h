//
// Created by Francisco Blanco on 2/24/2024.
//

#ifndef ENGINETEST_RENDERINGSYSTEMMOCK_H
#define ENGINETEST_RENDERINGSYSTEMMOCK_H

#include "../RenderingSystem.h"

class RenderingSystemMock : public RenderingSystem {
public:
    void init() override;
    void destroy() override;
    void render() override;
    void cleanScreen() override;

    RenderingSystemMock() = default;
    ~RenderingSystemMock() = default;
};


#endif //ENGINETEST_RENDERINGSYSTEMMOCK_H
