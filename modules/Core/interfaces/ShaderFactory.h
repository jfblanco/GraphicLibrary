#ifndef ENGINETEST_SHADERFACTORY_H
#define ENGINETEST_SHADERFACTORY_H

class Configuration;
class ShaderManager;
class ShaderFactory {
public:
    ShaderFactory() = default;
    ~ShaderFactory() = default;

    virtual void init(Configuration*, ShaderManager*)=0;
    virtual void destroy()=0;
};


#endif //ENGINETEST_SHADERFACTORY_H
