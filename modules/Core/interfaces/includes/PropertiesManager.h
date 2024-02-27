//
// Created by Francisco Blanco on 2/24/2024.
//

#ifndef ENGINETEST_PROPERTIESMANAGER_H
#define ENGINETEST_PROPERTIESMANAGER_H

#include <map>
#include "../ConfigurationSystem.h"

class PropertiesManager : public ConfigurationSystem {
public:
    PropertiesManager() = default;
    ~PropertiesManager() = default;

    void init(Configuration*) override;
    void destroy() override;
};


#endif //ENGINETEST_PROPERTIESMANAGER_H
