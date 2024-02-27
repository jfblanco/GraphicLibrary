#ifndef ENGINETEST_RESOURCESMANAGER_H
#define ENGINETEST_RESOURCESMANAGER_H

#include <vector>
#include <string>
#include <map>
#include "../../Core/external/glm/mat4x4.hpp"

class ConfigManager;
class RenderManager;
class Model;
class Joint;
class Skin;
class Animation;
class ChannelGLTF;
class FileGLTF;
class EntityManager;
class ResourcesManager {
public:
    ResourcesManager();
    ~ResourcesManager();

    void init(ConfigManager*, EntityManager*);
    void destroy(RenderManager*);

    void load3DModels();
    Model* getModel(const char*);
    Skin* getSkin(const char*);

private:
    std::map<std::string, Model*> models;
    std::map<std::string, Skin*> skins;
    std::string pathToResources;
    ConfigManager* configManager{};
    EntityManager* entityManager{};

    void printModelInformation(Model*);
    void loadGLTFModel(const char*);
    void loadOBJModel(const char*);
    void createEngineElements(FileGLTF*);
};



#endif //ENGINETEST_RESOURCESMANAGER_H
