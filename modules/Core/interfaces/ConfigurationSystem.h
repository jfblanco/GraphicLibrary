#ifndef CONFIGURATION_MANAGERSYSTEM_H
#define CONFIGURATION_MANAGERSYSTEM_H

#include <SDL2/SDL.h>
#include <string>

class Configuration;
class ConfigurationSystem {
public:
    virtual void init(Configuration*)=0;
    virtual void destroy()=0;
};

#endif //CONFIGURATION_MANAGERSYSTEM_H
