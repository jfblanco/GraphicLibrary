#ifndef ENGINETEST_CONFIGURATIONS_H
#define ENGINETEST_CONFIGURATIONS_H

#include <string>
#include <map>
#include <utility>
#include <SDLAPI.h>

class Configuration {
public:
    std::string pathToModelResources = "./res/properties.json";
    std::map<std::string, std::string> stringProperties;
    std::map<std::string, UnsignedInteger64> uintProperties;
    std::map<std::string, Boolean> boolProperties;

    Configuration() = default;
    ~Configuration() = default;

    UnsignedInteger64 getPropertyAsUInt16(const std::string& key) {
        auto result = this->uintProperties.find(key);
        UnsignedInteger64 returnedValue = -1;
        if(result != this->uintProperties.end()){
            returnedValue = result->second;
        }
        return returnedValue;
    }

    bool getPropertyAsBoolean(const std::string& key) {
        bool result = false;
        auto value = this->boolProperties.find(key);
        if(value != this->boolProperties.end()) {
            result = value->second;
        }
        return result;
    }

    std::string getPropertyAsString(const std::string& key){
        return this->stringProperties.find(key)->second;
    }

};

#endif //ENGINETEST_CONFIGURATIONS_H
