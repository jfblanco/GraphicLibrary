#ifndef ENGINETEST_RESOURCESMANAGER_H
#define ENGINETEST_RESOURCESMANAGER_H

#include <vector>
#include <string>
#include <map>
#include "../../Core/external/glm/mat4x4.hpp"

class Configuration;
class Renderable;
class Skin;
class Animation;
class ChannelGLTF;
class FileGLTF;
class EntityManager;
class ResourcesManager {
public:
    ResourcesManager() = default;
    ~ResourcesManager() = default;

    void init(Configuration*);
    void destroy();

    void load3DModels();
    Renderable* getRenderable(const char*);
    Skin* getSkin(const char*);

    std::map<std::string, Renderable*> models;
    std::map<std::string, Skin*> skins;
    std::string pathToModelResources;
    std::string pathToImagesResources;
    EntityManager* entityManager{};

    void printModelInformation(Renderable*);
    void loadGLTFModel(const char*);
    void loadOBJModel(const char*);
    void createEngineElements(FileGLTF*);
};



#endif //ENGINETEST_RESOURCESMANAGER_H
