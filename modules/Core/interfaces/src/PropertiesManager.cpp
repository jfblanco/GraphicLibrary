#include "../includes/PropertiesManager.h"
#include "../../entities/include/Configuration.h"
#include "../../external/jsoncpp/include/json/json.h"
#include <iostream>
#include <string>

Json::String readInputTestFile(const char* path) {
    FILE* file = fopen(path, "rb");
    if (!file)
        return "";
    fseek(file, 0, SEEK_END);
    auto const size = ftell(file);
    auto const usize = static_cast<size_t>(size);
    fseek(file, 0, SEEK_SET);
    auto buffer = new char[size + 1];
    buffer[size] = 0;
    Json::String text;
    if (fread(buffer, 1, usize, file) == usize)
        text = buffer;
    fclose(file);
    delete[] buffer;
    return text;
}

void saveProperty(Configuration *config, Json::Value::const_iterator property) {
    if(property->isString()) {
        config->stringProperties.insert(std::pair<std::string, std::string>(property.key().asString(), property->asString()));
    }
    if(property->isBool()) {
        config->boolProperties.insert(std::pair<std::string, SDL_bool>(property.key().asString(), property->asBool()));
    }
    if(property->isUInt64()) {
        config->uintProperties.insert(std::pair<std::string, Uint64>(property.key().asString(), property->asUInt64()));
    }
}

void loadProperties(Configuration *configuration) {
    JSONCPP_STRING err;
    Json::Value root;

    Json::CharReaderBuilder builder;

    Json::String input = readInputTestFile(configuration->pathToModelResources.c_str());

    builder.settings_["allowComments"] = false;
    builder.settings_["strictRoot"] = true;
    builder.settings_["allowDroppedNullPlaceholders"] = false;
    builder.settings_["allowNumericKeys"] = false;

    std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
    Json::String errors;

    if (!reader->parse(input.data(), input.data() + input.size(), &root, &errors)) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, std::string("Error reading ").append(configuration->pathToModelResources).append("\n\n").append(err).c_str());
        exit(5);
    }

    for(Json::Value::const_iterator rootIterator = root.begin() ; rootIterator != root.end() ; rootIterator++) {
        saveProperty(configuration, rootIterator);
        for(Json::Value::const_iterator firstLevel = rootIterator->begin() ; firstLevel != rootIterator->end() ; firstLevel++) {
            saveProperty(configuration, firstLevel);
            for(Json::Value::const_iterator secondLevel = firstLevel->begin() ; secondLevel != firstLevel->end() ; secondLevel++) {
                saveProperty(configuration, secondLevel);
            }
        }
    }
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, std::string().append("    - configuration init completed: ").append(std::to_string(configuration->stringProperties.size())).append(" String properties found").c_str());
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, std::string().append("    - configuration init completed: ").append(std::to_string(configuration->boolProperties.size())).append(" Bool properties found").c_str());
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, std::string().append("    - configuration init completed: ").append(std::to_string(configuration->uintProperties.size())).append(" Int properties found").c_str());
}

void PropertiesManager::init(Configuration* configurations) {
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Initializing [PropertiesManager]");
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, std::string("Reading properties from: ").append(configurations->pathToModelResources).c_str());
    loadProperties(configurations);
}

void PropertiesManager::destroy() {

}
