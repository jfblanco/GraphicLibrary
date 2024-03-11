#ifndef ENGINETEST_SHADERFACTORYMOCK_H
#define ENGINETEST_SHADERFACTORYMOCK_H

#include "../ShaderFactory.h"

class ShaderFactoryMock : public ShaderFactory {
public:
    ShaderFactoryMock() = default;
    ~ShaderFactoryMock() = default;

    void init(Configuration*, ShaderManager*) override;
    void destroy() override;
};


#endif //ENGINETEST_SHADERFACTORYMOCK_H
