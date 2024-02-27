#include "../include/ResourcesManager.h"
#include "../external/jsoncpp/include/json/json.h"
#include "glm/detail/type_quat.hpp"
#include <glm/glm.hpp>
#include <SDL3/SDL.h>
#include <filesystem>

struct ChannelGLTF {
    uint32_t node;
    std::vector<float> keyframes;
    std::vector<glm::vec4> rotation;
    std::vector<glm::vec3> translation;
    std::vector<glm::vec3> scale;
    std::string targetName;
};

struct SkinGLTF {
    std::string name;
    std::vector<glm::mat4> inverseBindMatrices;
    std::vector<uint32_t> joints;
};

struct MeshGLTF {
    std::string name;
    std::vector<uint16_t> indices;
    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> textureCoordinates;
    std::vector<uint8_t> joints;
    std::vector<glm::vec4> weights;
};

struct AnimationGLTF {
    std::string name;
    std::vector<ChannelGLTF> channels;
};

struct NodeGLTF {
    std::string name;
    glm::quat rotation = glm::quat(1.0f,0.0f,0.0f,0.0f);
    glm::vec4 position = glm::vec4(0.0f,0.0f,0.0f,0.0f);
    glm::vec3 scale = glm::vec3(1.0f,1.0f,1.0f);
    std::vector<uint32_t> children;
    uint32_t mesh = -1;
    SkinGLTF* skin;
};

struct FileGLTF {
    std::vector<NodeGLTF> nodes;
    std::vector<AnimationGLTF> animations;
    std::vector<MeshGLTF> meshes;
    std::vector<SkinGLTF> skins;
};

ResourcesManager::ResourcesManager() = default;

ResourcesManager::~ResourcesManager() {
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Destroying ResourcesManager");
}

void ResourcesManager::init(ConfigManager* _configManager, EntityManager* _entityManager) {
//    this->configManager = _configManager;
//    this->entityManager = _entityManager;
//    bool enableLogManager = this->configManager->getPropertyAsBoolean("logManagger::enableResourcesManagerLogger");
//    this->pathToResources = this->configManager->getPropertyAsString("modelPathFolder");
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "ResourcesManager Init completed");
}

void ResourcesManager::destroy(RenderManager *_renderManager) {
//    for(auto& skin : this->skins) {
//        skin.second->destroy(_renderManager);
//    }
}

void ResourcesManager::load3DModels() {
//    if(std::filesystem::exists(this->pathToResources)) {
//        for (const auto &file: std::filesystem::directory_iterator(this->pathToResources)) {
//            std::string filePath(file.path());
//            if(filePath.find(".gltf") != std::string::npos) {
//                if(this->logManager != nullptr) this->logManager->info(std::string("[    Loading GLTF: ").append(file.path()).append("    ]"));
//                this->loadGLTFModel(filePath.c_str());
//            }
//            if(filePath.find(".obj") != std::string::npos) {
//                if(this->logManager != nullptr) this->logManager->info(std::string("[    Loading OBJ: ").append(file.path()).append("    ]"));
//                this->loadOBJModel(filePath.c_str());
//            }
//        }
//    }
}

void split(const std::string &in, std::vector<std::string> &out, const std::string& token) {
//    out.clear();
//    std::string temp;
//    for (int i = 0; i < int(in.size()); i++) {
//        std::string test = in.substr(i, token.size());
//        if (test == token) {
//            if (!temp.empty()) {
//                out.push_back(temp);
//                temp.clear();
//                i += (int)token.size() - 1;
//            }
//            else {
//                out.emplace_back("");
//            }
//        }
//        else if (i + token.size() >= in.size()) {
//            temp += in.substr(i, token.size());
//            out.push_back(temp);
//            break;
//        } else {
//            temp += in[i];
//        }
//    }
}


void ResourcesManager::loadOBJModel(const char *_pathToFile) {
//    std::ifstream objFile;
//    objFile.open(_pathToFile, std::ios::in);
//    if(objFile.is_open()) {
//        auto* model = this->entityManager->getModelSystem()->createModel();
//        std::string line;
//        while(std::getline(objFile, line)){
//            if (line.substr(0,2)=="o "){
//                std::istringstream objectName(line.substr(2));
//                model->name = objectName.str();
//            }
//            if (line.substr(0,2)=="v "){
//                std::istringstream v(line.substr(2));
//                glm::vec3 vert;
//                double x,y,z;
//                v>>x;v>>y;v>>z;
//                vert=glm::vec3(x,y,z);
//                model->vertices.push_back(vert);
//
//            }
//            if (line.substr(0,3)=="vn "){
//                std::istringstream v(line.substr(3));
//                glm::vec3 vert;
//                double x,y,z;
//                v>>x;v>>y;v>>z;
//                vert = glm::vec3(x,y,z);
//                model->normals.push_back(vert);
//            }
//            if (line.substr(0,3)=="vt "){
//                std::istringstream v(line.substr(3));
//                glm::vec2 vert;
//                double x,y;
//                v>>x; v>>y;
//                vert = glm::vec2(x,y);
//                model->texture.push_back(vert);
//            }
//            if (line.substr(0,2)=="f "){
//                uint16_t a,b,c;
//                std::vector<std::string> faces;
//
//                split(line, faces, std::string(" "));
//
//                std::vector<std::string> face;
//                split(faces[1], face, std::string("/"));
//                std::istringstream fa(face[0]);
//                fa>>a;
//
//                split(faces[2], face, std::string("/"));
//                std::istringstream fb(face[0]);
//                fb>>b;
//
//                split(faces[3], face, std::string("/"));
//                std::istringstream fc(face[0]);
//                fc>>c;
//
//                a--;b--;c--;
//                model->index.push_back(a);
//                model->index.push_back(b);
//                model->index.push_back(c);
//            }
//        }
//        this->models.insert(std::pair<std::string, Model*>(model->name, model));
//        this->printModelInformation(model);
//        objFile.close();
//    }
}

void loadGLTFMeshPositionsFromFile(MeshGLTF *meshGltf, uint32_t positionIndex, Json::Value _accessors, Json::Value _buffersViews, std::ifstream *_jsonFile) {
//    uint16_t bufferView = _accessors[positionIndex]["bufferView"].asUInt();
//    uint32_t count = _accessors[positionIndex]["count"].as<uint32_t>();
//    std::string type = _accessors[positionIndex]["type"].asString();
//
//    uint32_t indicesByteLength = _buffersViews[bufferView]["byteLength"].as<uint32_t>();
//    uint32_t indicesByteOffset = _buffersViews[bufferView]["byteOffset"].as<uint32_t>();
//
//    if(_jsonFile->is_open()) {
//        meshGltf->positions.resize(count);
//        _jsonFile->seekg(indicesByteOffset);
//        _jsonFile->read(reinterpret_cast<char *>(meshGltf->positions.data()), indicesByteLength);
//    }
//    for(auto& vertice : model->vertices) {
//        vertice = rotationMatrix * scaleMatrix * vertice;
//    }
}

void loadGLTFMeshNormalsFromFile(MeshGLTF *meshGltf, uint32_t normalsIndex, Json::Value _accessors, Json::Value _buffersViews, std::ifstream *_jsonFile) {
//    uint16_t bufferView = _accessors[normalsIndex]["bufferView"].asUInt();
//    uint32_t count = _accessors[normalsIndex]["count"].as<uint32_t>();
//    std::string type = _accessors[normalsIndex]["type"].asString();
//
//    uint32_t indicesByteLength = _buffersViews[bufferView]["byteLength"].as<uint32_t>();
//    uint32_t indicesByteOffset = _buffersViews[bufferView]["byteOffset"].as<uint32_t>();
//
//    if(_jsonFile->is_open()) {
//        meshGltf->normals.resize(count);
//        _jsonFile->seekg(indicesByteOffset);
//        _jsonFile->read(reinterpret_cast<char *>(meshGltf->normals.data()), indicesByteLength);
//    }
}

void loadGLTFMeshTextureCoordinatesFromFile(MeshGLTF *meshGltf, uint32_t textCoordIndex, Json::Value _accessors, Json::Value _buffersViews, std::ifstream *_jsonFile) {
//    uint16_t bufferView = _accessors[textCoordIndex]["bufferView"].asUInt();
//    uint32_t count = _accessors[textCoordIndex]["count"].as<uint32_t>();
//    std::string type = _accessors[textCoordIndex]["type"].asString();
//
//    uint32_t indicesByteLength = _buffersViews[bufferView]["byteLength"].as<uint32_t>();
//    uint32_t indicesByteOffset = _buffersViews[bufferView]["byteOffset"].as<uint32_t>();
//
//    if(_jsonFile->is_open()) {
//        meshGltf->textureCoordinates.resize(count);
//        _jsonFile->seekg(indicesByteOffset);
//        _jsonFile->read(reinterpret_cast<char *>(meshGltf->textureCoordinates.data()), indicesByteLength);
//    }
}

void loadGLTFMeshJointsFromFile(MeshGLTF *meshGltf, uint32_t jointIndex, Json::Value _accessors, Json::Value _buffersViews, std::ifstream *_jsonFile) {
//    uint16_t bufferView = _accessors[jointIndex]["bufferView"].asUInt();
//    uint32_t count = _accessors[jointIndex]["count"].as<uint32_t>();
//    std::string type = _accessors[jointIndex]["type"].asString();
//
//    uint32_t indicesByteLength = _buffersViews[bufferView]["byteLength"].as<uint32_t>();
//    uint32_t indicesByteOffset = _buffersViews[bufferView]["byteOffset"].as<uint32_t>();
//
//    if(_jsonFile->is_open()) {
//        meshGltf->joints.resize(count * 4);
//        _jsonFile->seekg(indicesByteOffset);
//        _jsonFile->read((char*)meshGltf->joints.data(), indicesByteLength);
//        int j = 0;
//        for (int i = 0; i < temporaryIndexArray.size(); i += 4) {
//            model->joints[j].x = temporaryIndexArray[i];
//            model->joints[j].y = temporaryIndexArray[i + 1];
//            model->joints[j].z = temporaryIndexArray[i + 2];
//            model->joints[j].w = temporaryIndexArray[i + 3];
//            j++;
//        }
//    }
}

void loadGLTFMeshWeightsFromFile(MeshGLTF *meshGltf, uint32_t weightsIndex, Json::Value _accessors, Json::Value _buffersViews, std::ifstream *_jsonFile) {
//    uint16_t bufferView = _accessors[weightsIndex]["bufferView"].asUInt();
//    uint32_t count = _accessors[weightsIndex]["count"].as<uint32_t>();
//    std::string type = _accessors[weightsIndex]["type"].asString();
//
//    uint32_t indicesByteLength = _buffersViews[bufferView]["byteLength"].as<uint32_t>();
//    uint32_t indicesByteOffset = _buffersViews[bufferView]["byteOffset"].as<uint32_t>();
//
//    if(_jsonFile->is_open()) {
//        meshGltf->weights.resize(count);
//        _jsonFile->seekg(indicesByteOffset);
//        _jsonFile->read((char*)meshGltf->weights.data(), indicesByteLength);
//    }
}

void loadGLTFMeshIndicesFromFile(MeshGLTF *meshGltf, uint32_t indicesIndex, Json::Value _accessors, Json::Value _buffersViews, std::ifstream *_jsonFile) {
//    uint16_t bufferView = _accessors[indicesIndex]["bufferView"].asUInt();
//    uint32_t count = _accessors[indicesIndex]["count"].as<uint32_t>();
//    std::string type = _accessors[indicesIndex]["type"].asString();
//
//    uint32_t indicesByteLength = _buffersViews[bufferView]["byteLength"].as<uint32_t>();
//    uint32_t indicesByteOffset = _buffersViews[bufferView]["byteOffset"].as<uint32_t>();
//
//    if(_jsonFile->is_open()) {
//        meshGltf->indices.resize(count);
//        _jsonFile->seekg(indicesByteOffset);
//        _jsonFile->read((char*)meshGltf->indices.data(), indicesByteLength);
//    }
}

void loadGLTFMeshFromFile(FileGLTF *_fileGltf, Json::Value _mesh, const Json::Value& _accessors, const Json::Value& _buffersViews, std::ifstream *_jsonFile) {
//    MeshGLTF meshGltf;
//    meshGltf.name = _mesh["name"].asString();
//    for (auto primitive: _mesh["primitives"]) {
//        if(!primitive["attributes"]["POSITION"].isNull()) {
//            loadGLTFMeshPositionsFromFile(&meshGltf, primitive["attributes"]["POSITION"].as<uint32_t>(), _accessors, _buffersViews, _jsonFile);
//        }
//        if(!primitive["indices"].isNull()) {
//            loadGLTFMeshIndicesFromFile(&meshGltf, primitive["indices"].as<uint32_t>(), _accessors, _buffersViews, _jsonFile);
//        }
//        if(!primitive["attributes"]["NORMAL"].isNull()) {
//            loadGLTFMeshNormalsFromFile(&meshGltf, primitive["attributes"]["NORMAL"].as<uint32_t>(), _accessors, _buffersViews, _jsonFile);
//        }
//        if(!primitive["attributes"]["TEXCOORD_0"].isNull()) {
//            loadGLTFMeshTextureCoordinatesFromFile(&meshGltf, primitive["attributes"]["TEXCOORD_0"].as<uint32_t>(), _accessors, _buffersViews, _jsonFile);
//        }
//        if(!primitive["attributes"]["JOINTS_0"].isNull()) {
//            loadGLTFMeshJointsFromFile(&meshGltf, primitive["attributes"]["JOINTS_0"].as<uint32_t>(), _accessors, _buffersViews, _jsonFile);
//        }
//        if(!primitive["attributes"]["WEIGHTS_0"].isNull()) {
//            loadGLTFMeshWeightsFromFile(&meshGltf, primitive["attributes"]["WEIGHTS_0"].as<uint32_t>(), _accessors, _buffersViews, _jsonFile);
//        }
//    }
//    _fileGltf->meshes.push_back(meshGltf);
}

Model* createModelFromNode(NodeGLTF *nodeGltf, MeshGLTF *meshGltf, EntityManager* _entityManager) {
//    auto* model = _entityManager->getModelSystem()->createModel();
//    model->name = nodeGltf->name;
//    model->position = nodeGltf->position;
//    model->scale = nodeGltf->scale;
//    model->eulerAngles = glm::eulerAngles(nodeGltf->rotation);
//    model->vertices.insert(model->vertices.end(), meshGltf->positions.begin(), meshGltf->positions.end());
//    model->index.insert(model->index.end(), meshGltf->indices.begin(), meshGltf->indices.end());
//    model->normals.insert(model->normals.end(), meshGltf->normals.begin(), meshGltf->normals.end());
//    model->texture.insert(model->texture.end(), meshGltf->textureCoordinates.begin(), meshGltf->textureCoordinates.end());
//    model->weights.insert(model->weights.end(), meshGltf->weights.begin(), meshGltf->weights.end());
//    for(int i=0; i<meshGltf->joints.size();i+=4) {
//        model->joints.push_back(glm::vec4(meshGltf->joints[i], meshGltf->joints[i+1], meshGltf->joints[i+2], meshGltf->joints[i+3]));
//    }
//    return model;
    return NULL;
}

Skin* createSkinFromNode(SkinGLTF *skinGltf, std::vector<NodeGLTF>* nodes){
//    auto *skin = new Skin();
//    skin->name = skinGltf->name;
//    int i = 0;
//    for(auto& jointIndex : skinGltf->joints) {
//        auto *joint = new Joint();
//        joint->index = jointIndex;
//        joint->name = (*nodes)[jointIndex].name;
//        joint->rotation = (*nodes)[jointIndex].rotation;
//        joint->eulerAngles = glm::eulerAngles(joint->rotation);
//        joint->scale = (*nodes)[jointIndex].scale;
//        joint->tall = (*nodes)[jointIndex].position;
//        joint->jointToModelMatrix = skinGltf->inverseBindMatrices[i];
//        for(auto& child : (*nodes)[jointIndex].children) {
//            joint->children.push_back(child);
//        }
//        skin->joints.push_back(joint);
//        i++;
//    }
//    for(auto& node : *nodes) {
//        if(skin->name == node.name) {
//            skin->position = node.position;
//            skin->rotation = node.rotation;
//            skin->origin = skin->position * glm::toMat4(skin->rotation);
//            skin->worldToSkinMatrix = skin->worldToSkinMatrix * glm::toMat4(skin->rotation);
//            skin->worldToSkinMatrix[3].x = skin->position.x;
//            skin->worldToSkinMatrix[3].y = skin->position.y;
//            skin->worldToSkinMatrix[3].z = skin->position.z;
//        }
//    }
//    return skin;
    return NULL;
}

void createSkinHierarchy(Skin *skin) {
//    for(auto& joint : skin->joints) {
//        for(auto& child : joint->children) {
//            for(auto& jointChild : skin->joints) {
//                if(jointChild->index == child) {
//                    jointChild->parent = joint;
//                    joint->childrenObjects.push_back(jointChild);
//                    break;
//                }
//            }
//        }
//    }
//    for(auto& joint : skin->joints) {
//        if(joint->parent == nullptr) {
//            joint->modelToJointMatrix = joint->modelToJointMatrix * skin->worldToSkinMatrix;
//        }
//        glm::vec4 rotatedTall = joint->modelToJointMatrix * joint->tall;
//        joint->modelToJointMatrix = joint->modelToJointMatrix * glm::toMat4(joint->rotation);
//        joint->modelToJointMatrix[3].x += rotatedTall.x;
//        joint->modelToJointMatrix[3].y += rotatedTall.y;
//        joint->modelToJointMatrix[3].z += rotatedTall.z;
//        for(auto& child : joint->childrenObjects) {
//            child->modelToJointMatrix = child->modelToJointMatrix * joint->modelToJointMatrix;
//        }
//        joint->size.resize(2);
//        joint->size[0] = joint->modelToJointMatrix * glm::vec4(0.0,0.0,0.0,1.0);
//        joint->size[1] = joint->modelToJointMatrix * glm::vec4(0.0,1.0,0.0,1.0);
//    }
//
//    skin->currentAnimationMatrices.resize(skin->joints.size());
//    skin->modelToJointMatrices.resize(skin->joints.size());
//    skin->setCurrentAnimationMatricesIdentity();
}

void loadGLTFSampler(Animation* _animation, std::vector<ChannelGLTF>* channels, float *animationStartTime, float *animationEndTime, Skin* _skin) {
//    int index = 0;
//    for(auto& joint : _skin->joints) {
//        std::vector<glm::vec4>* rotation = nullptr;
//        std::vector<glm::vec3>* translation = nullptr;
//        std::vector<float>* keyFrames = nullptr;
//
//        for(auto& channel : *channels) {
//            if(channel.node == joint->index && channel.targetName == "translation") {
//                translation = &(channel.translation);
//            }
//            if(channel.node == joint->index && channel.targetName == "rotation") {
//                rotation = &(channel.rotation);
//                keyFrames = &(channel.keyframes);
//            }
//        }
//
//        if(keyFrames != nullptr) {
//            for(int i = 0; i < keyFrames->size() - 1; i++) {
//                auto *sampler = new Sampler();
//                sampler->start = (*keyFrames)[i];
//                if (sampler->start < *animationStartTime) {
//                    *animationStartTime = sampler->start;
//                }
//                sampler->end = (*keyFrames)[i + 1];
//                if (sampler->end > *animationEndTime) {
//                    *animationEndTime = sampler->end;
//                }
//                sampler->timeDifference = sampler->end - sampler->start;
//
//                if(translation != nullptr) {
//                    sampler->startRotation = glm::quat((*rotation)[i].w, (*rotation)[i].x, (*rotation)[i].y, (*rotation)[i].z);
//                    sampler->endRotation = glm::quat((*rotation)[i + 1].w, (*rotation)[i + 1].x, (*rotation)[i + 1].y, (*rotation)[i + 1].z);
//                }
//
//                if(translation != nullptr) {
//                    sampler->startPosition = (*translation)[i];
//                    sampler->endPosition = (*translation)[i + 1];
//                }
//                sampler->startEuler = glm::eulerAngles(sampler->startRotation);
//                sampler->endEuler = glm::eulerAngles(sampler->endRotation);
//
//                sampler->interpolationVector = sampler->endRotation - sampler->startRotation;
//                _animation->animatedBones[index]->samplers.push_back(sampler);
//            }
//            if(!_animation->animatedBones.empty() && _animation->animatedBones[index] != nullptr && !_animation->animatedBones[index]->samplers.empty()) {
//                _animation->animatedBones[index]->currentSampler = _animation->animatedBones[index]->samplers[0];
//            }
//        }
//        index++;
//    }
}

void createAnimationFromNode(ResourcesManager *_resourceManager, const std::string& skinName, AnimationGLTF *_animationGltf) {
//    auto *animation = new Animation();
//    animation->name = _animationGltf->name;
//
//    auto *skin = _resourceManager->getSkin(skinName.c_str());
//
//    for(int i = 0; i < skin->joints.size(); i ++) {
//        animation->animatedBones.push_back(new AnimatedBone());
//    }
//    loadGLTFSampler(animation, &(_animationGltf->channels), &(animation->startTime), &(animation->endTime), skin);
//    skin->animations.insert(std::pair<std::string, Animation*>(animation->name, animation));
//    skin->currentAnimation = animation;
}

void ResourcesManager::createEngineElements(FileGLTF *_fileGltf) {
//    for(auto& node : _fileGltf->nodes) {
//        if(node.mesh != -1) {
//            this->models.insert(std::pair<std::string,Model*>(node.name, createModelFromNode(&node, &(_fileGltf->meshes[node.mesh]), this->entityManager)));
//        }
//    }
//    for(auto& skinGltf : _fileGltf->skins) {
//        auto *skin = createSkinFromNode(&skinGltf, &(_fileGltf->nodes));
//        createSkinHierarchy(skin);
//        this->skins.insert(std::pair<std::string,Skin*>(skinGltf.name, skin));
//    }
//    for(auto& animationGltf : _fileGltf->animations) {
//        createAnimationFromNode(this, _fileGltf->skins[0].name, &animationGltf);
//    }
}

void loadGLTFSkinFromFile(FileGLTF *_fileGltf, Json::Value _skin, const Json::Value& _accessors, const Json::Value& _buffersViews, std::ifstream *_jsonFile) {
//    SkinGLTF skinGltf;
//    skinGltf.name = _skin["name"].asString();
//
//    uint32_t inversedMatrixAccessor = _skin["inverseBindMatrices"].as<uint32_t>();
//    uint32_t inversedMatrixBufferView = _accessors[inversedMatrixAccessor]["bufferView"].as<uint32_t>();
//    std::string inversedMatrixBufferViewType = _accessors[inversedMatrixAccessor]["type"].asString();
//    uint32_t count = _accessors[inversedMatrixAccessor]["count"].as<uint32_t>();
//    std::streamoff byteOffset = _buffersViews[inversedMatrixBufferView]["byteOffset"].as<std::streamoff>();
//    std::streamoff arrayByteLenght = _buffersViews[inversedMatrixBufferView]["byteLength"].as<std::streamoff>();
//
//    if(_jsonFile->is_open() && inversedMatrixBufferViewType == "MAT4") {
//        skinGltf.inverseBindMatrices.resize(count);
//        _jsonFile->seekg(byteOffset);
//        _jsonFile->read((char*)skinGltf.inverseBindMatrices.data(), arrayByteLenght);
//    }
//
//    for(const Json::Value& joint : _skin["joints"]) {
//        skinGltf.joints.push_back(joint.as<uint32_t>());
//    }
//    _fileGltf->skins.push_back(skinGltf);
}

void loadGLTFAnimationFromFile(FileGLTF *_fileGltf, Json::Value _animation, const Json::Value& _accessors, const Json::Value& _buffersViews, std::ifstream *_jsonFile) {
//    AnimationGLTF animationGltf;
//    animationGltf.name = _animation["name"].asString();
//    for(Json::Value channel : _animation["channels"]) {
//        ChannelGLTF channelGltf;
//        uint32_t sampler = channel["sampler"].as<uint32_t>();
//        channelGltf.node = channel["target"]["node"].as<uint32_t>();
//        channelGltf.targetName = channel["target"]["path"].asString();
//
//        if(channelGltf.targetName == "rotation") {
//            uint32_t input = _animation["samplers"][sampler]["input"].as<uint32_t>();
//            uint32_t output = _animation["samplers"][sampler]["output"].as<uint32_t>();
//
//            uint32_t bufferView = _accessors[input]["bufferView"].as<uint32_t>();
//            uint32_t count = _accessors[input]["count"].as<uint32_t>();
//            std::string type = _accessors[input]["type"].asString();
//
//            uint32_t byteOffsetChannel = _buffersViews[bufferView]["byteOffset"].as<uint32_t>();
//            uint32_t byteLength = _buffersViews[bufferView]["byteLength"].as<uint32_t>();
//
//            uint32_t outputBufferView = _accessors[output]["bufferView"].as<uint32_t>();
//            uint32_t outputCount = _accessors[output]["count"].as<uint32_t>();
//            std::string outputType = _accessors[output]["type"].asString();
//
//            uint32_t outputByteOffset = _buffersViews[outputBufferView]["byteOffset"].as<uint32_t>();
//            uint32_t outputByteLength = _buffersViews[outputBufferView]["byteLength"].as<uint32_t>();
//
//            channelGltf.keyframes.resize(count);
//            _jsonFile->seekg(byteOffsetChannel);
//            _jsonFile->read((char *) channelGltf.keyframes.data(), byteLength);
//
//            channelGltf.rotation.resize(count);
//            _jsonFile->seekg(outputByteOffset);
//            _jsonFile->read((char *) channelGltf.rotation.data(), outputByteLength);
//        }
//
//        if(channelGltf.targetName == "translation") {
//            uint32_t input = _animation["samplers"][sampler]["input"].as<uint32_t>();
//            uint32_t output = _animation["samplers"][sampler]["output"].as<uint32_t>();
//
//            uint32_t bufferView = _accessors[input]["bufferView"].as<uint32_t>();
//            uint32_t count = _accessors[input]["count"].as<uint32_t>();
//            std::string type = _accessors[input]["type"].asString();
//
//            uint32_t byteOffsetChannel = _buffersViews[bufferView]["byteOffset"].as<uint32_t>();
//            uint32_t byteLength = _buffersViews[bufferView]["byteLength"].as<uint32_t>();
//
//            uint32_t outputBufferView = _accessors[output]["bufferView"].as<uint32_t>();
//            uint32_t outputCount = _accessors[output]["count"].as<uint32_t>();
//            std::string outputType = _accessors[output]["type"].asString();
//
//            uint32_t outputByteOffset = _buffersViews[outputBufferView]["byteOffset"].as<uint32_t>();
//            uint32_t outputByteLength = _buffersViews[outputBufferView]["byteLength"].as<uint32_t>();
//
//            channelGltf.keyframes.resize(count);
//            _jsonFile->seekg(byteOffsetChannel);
//            _jsonFile->read((char *) channelGltf.keyframes.data(), byteLength);
//
//            channelGltf.translation.resize(count);
//            _jsonFile->seekg(outputByteOffset);
//            _jsonFile->read((char *) channelGltf.translation.data(), outputByteLength);
//        }
//        animationGltf.channels.push_back(channelGltf);
//    }
//    _fileGltf->animations.push_back(animationGltf);
}
void loadGLTFNodeFromFile(FileGLTF *_fileGltf, Json::Value _node, const Json::Value& _accessors, const Json::Value& _buffersViews, std::ifstream *_jsonFile) {
//    NodeGLTF nodeGltf;
//    nodeGltf.name = _node["name"].asString();
//
//    if(!_node["translation"].isNull()) {
//        nodeGltf.position = glm::vec4(_node["translation"][0].asFloat(), _node["translation"][1].asFloat(), _node["translation"][2].asFloat(), 0.0f);
//    }
//    if(!_node["mesh"].isNull()) {
//        nodeGltf.mesh =_node["mesh"].as<uint32_t>();
//    }
//    if(!_node["scale"].isNull()) {
//        nodeGltf.scale = glm::vec3(_node["scale"][0].asFloat(), _node["scale"][1].asFloat(), _node["scale"][2].asFloat());
//    }
//    if(!_node["rotation"].isNull()) {
//        nodeGltf.rotation = glm::quat(_node["rotation"][3].asFloat(), _node["rotation"][0].asFloat(), _node["rotation"][1].asFloat(), _node["rotation"][2].asFloat());
//    }
//    if(!_node["children"].isNull()) {
//        for(const Json::Value& child : _node["children"]) {
//            nodeGltf.children.push_back(child.as<uint32_t>());
//        }
//    }
//    _fileGltf->nodes.push_back(nodeGltf);
}

void ResourcesManager::loadGLTFModel(const char* pathToModel) {
//    std::ifstream jsonFile;
//    JSONCPP_STRING err;
//    Json::Value root;
//    Json::CharReaderBuilder builder;
//    jsonFile.open(pathToModel);
//
//    if (!parseFromStream(builder, jsonFile, &root, &err)) {
//        if(this->logManager != nullptr) this->logManager->error(std::string("Error reading:").append(pathToModel));
//    }
//
//    std::string pathToBinaryFile(this->pathToResources);
//    pathToBinaryFile.append(root["buffers"][0]["uri"].asString());
//    std::ifstream dataBufferFile;
//    dataBufferFile.open(pathToBinaryFile, std::ios::binary);
//    FileGLTF fileGltf;
//    if(!root["nodes"].isNull()) {
//        for(const Json::Value& node : root["nodes"]) {
//            loadGLTFNodeFromFile(&fileGltf, node, root["accessors"], root["bufferViews"], &dataBufferFile);
//        }
//    }
//    if(!root["meshes"].isNull()) {
//        for(const Json::Value& mesh : root["meshes"]) {
//            loadGLTFMeshFromFile(&fileGltf, mesh, root["accessors"], root["bufferViews"], &dataBufferFile);
//        }
//    }
//    if(!root["skins"].isNull()) {
//        for(const Json::Value& skin : root["skins"]) {
//            loadGLTFSkinFromFile(&fileGltf, skin, root["accessors"], root["bufferViews"], &dataBufferFile);
//        }
//    }
//    if(!root["animations"].isNull()) {
//        for(const Json::Value& animation : root["animations"]) {
//            loadGLTFAnimationFromFile(&fileGltf, animation, root["accessors"], root["bufferViews"], &dataBufferFile);
//        }
//    }
//    dataBufferFile.close();
//    jsonFile.close();
//    createEngineElements(&fileGltf);
}

void ResourcesManager::printModelInformation(Model* _model) {
//    if(this->logManager != nullptr) {
//        this->logManager->info(std::string("|        Model: ").append(_model->name));
//        this->logManager->info(std::string("|            Vertex: ").append(std::to_string(_model->vertices.size())));
//        this->logManager->info(std::string("|            Normal: ").append(std::to_string(_model->normals.size())));
//        this->logManager->info(std::string("|            Texture: ").append(std::to_string(_model->texture.size())));
//        this->logManager->info(std::string("|            Indices: ").append(std::to_string(_model->index.size())));
//    }
}

Model* ResourcesManager::getModel(const char * _modelName) {
//    auto result = this->models.find(_modelName);
//    if(result != this->models.end()){
//        return result->second;
//    }
//    return nullptr;
    return NULL;
}

Skin* ResourcesManager::getSkin(const char * _skinName) {
//    auto result = this->skins.find(_skinName);
//    if(result != this->skins.end()){
//        return result->second;
//    }
//    return nullptr;
    return NULL;
}

