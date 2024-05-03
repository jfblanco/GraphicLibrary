#include "../include/ResourcesManager.h"
#include "../entities/include/Configuration.h"
#include "../external/jsoncpp/include/json/json.h"

#include "../entities/include/Texture.h"
#include "../entities/include/Skin.h"
#include "../entities/include/Joint.h"
#include "../entities/include/Sampler.h"
#include "../entities/include/Animation.h"
#include "../entities/include/AnimatedBone.h"

#include "../../Render/include/Renderable.h"
#include "../../Render/include/Material.h"

#include <glm/detail/type_quat.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/common.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <filesystem>
#include <iostream>
#include <fstream>

#include <GL/glew.h>

struct ChannelGLTF {
    Uint16 node;
    std::vector<float> keyframes;
    std::vector<glm::vec4> rotation;
    std::vector<glm::vec3> translation;
    std::vector<glm::vec3> scale;
    std::string targetName;
};

struct MetallicRoughnessGLTF {
    Uint8 baseColorTexture = SDL_MAX_UINT8;
    GLfloat metallicFactor;
    GLfloat roughnessFactor;

};

struct NormalGLTF {
    Uint8 texture = SDL_MAX_UINT8;
};

struct HeightGLTF {
    Uint8 texture = SDL_MAX_UINT8;
};

struct MaterialGLTF {
    std::string name;
    NormalGLTF normalGltf;
    HeightGLTF heightGltf;
    MetallicRoughnessGLTF metallicRoughnessGltf;
};

struct ImageGLTF {
    std::string name;
    std::string source;
};

struct TextureGLTF {
    Uint8 sampler;
    Uint8 source;
};

struct SkinGLTF {
    std::string name;
    std::vector<glm::mat4> inverseBindMatrices;
    std::vector<Uint32> joints;
};

struct MeshGLTF {
    std::string name;
    std::vector<Uint16> indices;
    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> textureCoordinates;
    std::vector<glm::vec4> textureTangent;
    std::vector<glm::vec3> textureBitangent;
    std::vector<uint8_t> joints;
    std::vector<glm::vec4> weights;
    Uint8 material = SDL_MAX_UINT8;
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
    std::vector<Uint32> children;
    Uint8 mesh = SDL_MAX_UINT8;
    SkinGLTF* skin;
};

struct FileGLTF {
    std::vector<NodeGLTF> nodes;
    std::vector<AnimationGLTF> animations;
    std::vector<MeshGLTF> meshes;
    std::vector<SkinGLTF> skins;
    std::vector<MaterialGLTF> materials;
    std::vector<TextureGLTF> textures;
    std::vector<ImageGLTF> images;
};

void ResourcesManager::init(Configuration* configuration) {
    this->pathToModelResources = configuration->getPropertyAsString("modelPathFolder");
    this->pathToImagesResources = configuration->getPropertyAsString("imagePathFolder");
    if(!(IMG_Init(IMG_INIT_PNG || IMG_INIT_JPG))) {
        SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "[ResourcesManager] SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
    }
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "[ResourcesManager] Init completed");
}

void ResourcesManager::destroy() {
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Destroying ResourcesManager");
}

void createSimpleTriangle(ResourcesManager* resourcesManager) {
    auto *renderable = new Renderable();
    renderable->vertices.push_back(glm::vec3(-0.5f, -0.5f, 0.0));
    renderable->vertices.push_back(glm::vec3(-0.5f, 0.5f, 0.0));
    renderable->vertices.push_back(glm::vec3(0.5f, 0.5f, 0.0));
    renderable->vertices.push_back(glm::vec3(0.5f, -0.5f, 0.0));
    renderable->index.push_back(0);
    renderable->index.push_back(1);
    renderable->index.push_back(2);
    renderable->index.push_back(0);
    renderable->index.push_back(2);
    renderable->index.push_back(3);
    resourcesManager->models.insert(std::pair<std::string, Renderable*>("simpleTriangle", renderable));
}

void ResourcesManager::load3DModels() {
    createSimpleTriangle(this);
    if(std::filesystem::exists(this->pathToModelResources)) {
        for (const auto &file: std::filesystem::directory_iterator(this->pathToModelResources)) {
            std::string filePath = file.path().string();
            if(filePath.find(".gltf") != std::string::npos) {
                SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, std::string("[    Loading GLTF: ").append(filePath).append("    ]").c_str());
                this->loadGLTFModel(filePath.c_str());
            }
            if(filePath.find(".obj") != std::string::npos) {
                SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, std::string("[    Loading OBJ: ").append(filePath).append("    ]").c_str());
                this->loadOBJModel(filePath.c_str());
            }
        }
    }
}

void split(const std::string &in, std::vector<std::string> &out, const std::string& token) {
    out.clear();
    std::string temp;
    for (int i = 0; i < int(in.size()); i++) {
        std::string test = in.substr(i, token.size());
        if (test == token) {
            if (!temp.empty()) {
                out.push_back(temp);
                temp.clear();
                i += (int)token.size() - 1;
            }
            else {
                out.emplace_back("");
            }
        }
        else if (i + token.size() >= in.size()) {
            temp += in.substr(i, token.size());
            out.push_back(temp);
            break;
        } else {
            temp += in[i];
        }
    }
}

void ResourcesManager::loadOBJModel(const char *_pathToFile) {
    std::ifstream objFile;
    objFile.open(_pathToFile, std::ios::in);
    if(objFile.is_open()) {
        auto* model = new Renderable();
        std::string line;
        while(std::getline(objFile, line)){
            if (line.substr(0,2)=="o "){
                std::istringstream objectName(line.substr(2));
                model->name = objectName.str();
            }
            if (line.substr(0,2)=="v "){
                std::istringstream v(line.substr(2));
                glm::vec3 vert;
                double x,y,z;
                v>>x;v>>y;v>>z;
                vert=glm::vec3(x,y,z);
                model->vertices.push_back(vert);

            }
            if (line.substr(0,3)=="vn "){
                std::istringstream v(line.substr(3));
                glm::vec3 vert;
                double x,y,z;
                v>>x;v>>y;v>>z;
                vert = glm::vec3(x,y,z);
                model->normals.push_back(vert);
            }
            if (line.substr(0,3)=="vt "){
                std::istringstream v(line.substr(3));
                glm::vec2 vert;
                double x,y;
                v>>x; v>>y;
                vert = glm::vec2(x,y);
                model->texture.push_back(vert);
            }
            if (line.substr(0,2)=="f "){
                Uint16 a,b,c;
                std::vector<std::string> faces;

                split(line, faces, std::string(" "));

                std::vector<std::string> face;
                split(faces[1], face, std::string("/"));
                std::istringstream fa(face[0]);
                fa>>a;

                split(faces[2], face, std::string("/"));
                std::istringstream fb(face[0]);
                fb>>b;

                split(faces[3], face, std::string("/"));
                std::istringstream fc(face[0]);
                fc>>c;

                a--;b--;c--;
                model->index.push_back(a);
                model->index.push_back(b);
                model->index.push_back(c);
            }
        }
        this->models.insert(std::pair<std::string, Renderable*>(model->name, model));
        this->printModelInformation(model);
        objFile.close();
    }
}

void loadGLTFMeshPositionsFromFile(MeshGLTF *meshGltf, Uint32 positionIndex, Json::Value _accessors, Json::Value _buffersViews, std::ifstream *_jsonFile) {
    Uint16 bufferView = _accessors[positionIndex]["bufferView"].asUInt();
    Uint32 count = _accessors[positionIndex]["count"].as<Uint32>();
    std::string type = _accessors[positionIndex]["type"].asString();

    Uint32 indicesByteLength = _buffersViews[bufferView]["byteLength"].as<Uint32>();
    Uint32 indicesByteOffset = _buffersViews[bufferView]["byteOffset"].as<Uint32>();

    if(_jsonFile->is_open()) {
        meshGltf->positions.resize(count);
        _jsonFile->seekg(indicesByteOffset);
        _jsonFile->read(reinterpret_cast<char *>(meshGltf->positions.data()), indicesByteLength);
    }
//    for(auto& vertice : model->vertices) {
//        vertice = rotationMatrix * scaleMatrix * vertice;
//    }
}

void loadGLTFMeshNormalsFromFile(MeshGLTF *meshGltf, Uint32 normalsIndex, Json::Value _accessors, Json::Value _buffersViews, std::ifstream *_jsonFile) {
    Uint16 bufferView = _accessors[normalsIndex]["bufferView"].asUInt();
    Uint32 count = _accessors[normalsIndex]["count"].as<Uint32>();
    std::string type = _accessors[normalsIndex]["type"].asString();

    Uint32 indicesByteLength = _buffersViews[bufferView]["byteLength"].as<Uint32>();
    Uint32 indicesByteOffset = _buffersViews[bufferView]["byteOffset"].as<Uint32>();

    if(_jsonFile->is_open()) {
        meshGltf->normals.resize(count);
        _jsonFile->seekg(indicesByteOffset);
        _jsonFile->read(reinterpret_cast<char *>(meshGltf->normals.data()), indicesByteLength);
    }
}

void loadGLTFMeshTextureCoordinatesFromFile(MeshGLTF *meshGltf, Uint32 textCoordIndex, Json::Value _accessors, Json::Value _buffersViews, std::ifstream *_jsonFile) {
    Uint16 bufferView = _accessors[textCoordIndex]["bufferView"].asUInt();
    Uint32 count = _accessors[textCoordIndex]["count"].as<Uint32>();
    std::string type = _accessors[textCoordIndex]["type"].asString();

    Uint32 indicesByteLength = _buffersViews[bufferView]["byteLength"].as<Uint32>();
    Uint32 indicesByteOffset = _buffersViews[bufferView]["byteOffset"].as<Uint32>();

    if(_jsonFile->is_open()) {
        meshGltf->textureCoordinates.resize(count);
        _jsonFile->seekg(indicesByteOffset);
        _jsonFile->read(reinterpret_cast<char *>(meshGltf->textureCoordinates.data()), indicesByteLength);
    }
}

void loadGLTFMeshTangentFromFile(MeshGLTF *meshGltf, Uint32 textCoordIndex, Json::Value _accessors, Json::Value _buffersViews, std::ifstream *_jsonFile) {
    Uint16 bufferView = _accessors[textCoordIndex]["bufferView"].asUInt();
    Uint32 count = _accessors[textCoordIndex]["count"].as<Uint32>();
    std::string type = _accessors[textCoordIndex]["type"].asString();

    Uint32 indicesByteLength = _buffersViews[bufferView]["byteLength"].as<Uint32>();
    Uint32 indicesByteOffset = _buffersViews[bufferView]["byteOffset"].as<Uint32>();

    if(_jsonFile->is_open()) {
        meshGltf->textureTangent.resize(count);
        _jsonFile->seekg(indicesByteOffset);
        _jsonFile->read(reinterpret_cast<char *>(meshGltf->textureTangent.data()), indicesByteLength);
    }
}

void loadGLTFMeshJointsFromFile(MeshGLTF *meshGltf, Uint32 jointIndex, Json::Value _accessors, Json::Value _buffersViews, std::ifstream *_jsonFile) {
    Uint16 bufferView = _accessors[jointIndex]["bufferView"].asUInt();
    Uint32 count = _accessors[jointIndex]["count"].as<Uint32>();
    std::string type = _accessors[jointIndex]["type"].asString();

    Uint32 indicesByteLength = _buffersViews[bufferView]["byteLength"].as<Uint32>();
    Uint32 indicesByteOffset = _buffersViews[bufferView]["byteOffset"].as<Uint32>();

    if(_jsonFile->is_open()) {
        meshGltf->joints.resize(count * 4);
        _jsonFile->seekg(indicesByteOffset);
        _jsonFile->read((char*)meshGltf->joints.data(), indicesByteLength);
//        int j = 0;
//        for (int i = 0; i < temporaryIndexArray.size(); i += 4) {
//            model->joints[j].x = temporaryIndexArray[i];
//            model->joints[j].y = temporaryIndexArray[i + 1];
//            model->joints[j].z = temporaryIndexArray[i + 2];
//            model->joints[j].w = temporaryIndexArray[i + 3];
//            j++;
//        }
    }
}

void loadGLTFMeshWeightsFromFile(MeshGLTF *meshGltf, Uint32 weightsIndex, Json::Value _accessors, Json::Value _buffersViews, std::ifstream *_jsonFile) {
    Uint16 bufferView = _accessors[weightsIndex]["bufferView"].asUInt();
    Uint32 count = _accessors[weightsIndex]["count"].as<Uint32>();
    std::string type = _accessors[weightsIndex]["type"].asString();

    Uint32 indicesByteLength = _buffersViews[bufferView]["byteLength"].as<Uint32>();
    Uint32 indicesByteOffset = _buffersViews[bufferView]["byteOffset"].as<Uint32>();

    if(_jsonFile->is_open()) {
        meshGltf->weights.resize(count);
        _jsonFile->seekg(indicesByteOffset);
        _jsonFile->read((char*)meshGltf->weights.data(), indicesByteLength);
    }
}

void loadGLTFMeshIndicesFromFile(MeshGLTF *meshGltf, Uint32 indicesIndex, Json::Value _accessors, Json::Value _buffersViews, std::ifstream *_jsonFile) {
    Uint16 bufferView = _accessors[indicesIndex]["bufferView"].asUInt();
    Uint32 count = _accessors[indicesIndex]["count"].as<Uint32>();
    std::string type = _accessors[indicesIndex]["type"].asString();

    Uint32 indicesByteLength = _buffersViews[bufferView]["byteLength"].as<Uint32>();
    Uint32 indicesByteOffset = _buffersViews[bufferView]["byteOffset"].as<Uint32>();

    if(_jsonFile->is_open()) {
        meshGltf->indices.resize(count);
        _jsonFile->seekg(indicesByteOffset);
        _jsonFile->read((char*)meshGltf->indices.data(), indicesByteLength);
    }
}

void loadGLTFMeshFromFile(FileGLTF *_fileGltf, Json::Value _mesh, const Json::Value& _accessors, const Json::Value& _buffersViews, std::ifstream *_jsonFile) {
    MeshGLTF meshGltf;
    meshGltf.name = _mesh["name"].asString();
    for (auto primitive: _mesh["primitives"]) {
        if(!primitive["attributes"]["POSITION"].isNull()) {
            loadGLTFMeshPositionsFromFile(&meshGltf, primitive["attributes"]["POSITION"].as<Uint32>(), _accessors, _buffersViews, _jsonFile);
        }
        if(!primitive["indices"].isNull()) {
            loadGLTFMeshIndicesFromFile(&meshGltf, primitive["indices"].as<Uint32>(), _accessors, _buffersViews, _jsonFile);
        }
        if(!primitive["material"].isNull()) {
            meshGltf.material = primitive["material"].as<Uint32>();
        }
        if(!primitive["attributes"]["NORMAL"].isNull()) {
            loadGLTFMeshNormalsFromFile(&meshGltf, primitive["attributes"]["NORMAL"].as<Uint32>(), _accessors, _buffersViews, _jsonFile);
        }
        if(!primitive["attributes"]["TEXCOORD_0"].isNull()) {
            loadGLTFMeshTextureCoordinatesFromFile(&meshGltf, primitive["attributes"]["TEXCOORD_0"].as<Uint32>(), _accessors, _buffersViews, _jsonFile);
        }
        if(!primitive["attributes"]["TANGENT"].isNull()) {
            loadGLTFMeshTangentFromFile(&meshGltf, primitive["attributes"]["TANGENT"].as<Uint32>(), _accessors, _buffersViews, _jsonFile);
        }
        if(!primitive["attributes"]["JOINTS_0"].isNull()) {
            loadGLTFMeshJointsFromFile(&meshGltf, primitive["attributes"]["JOINTS_0"].as<Uint32>(), _accessors, _buffersViews, _jsonFile);
        }
        if(!primitive["attributes"]["WEIGHTS_0"].isNull()) {
            loadGLTFMeshWeightsFromFile(&meshGltf, primitive["attributes"]["WEIGHTS_0"].as<Uint32>(), _accessors, _buffersViews, _jsonFile);
        }
    }
    // Vertex Tangent and Bi-tangent
//    if(meshGltf.normals.size() == meshGltf.textureTangent.size()) {
//        meshGltf.textureBitangent.resize(meshGltf.normals.size());
//        for(Uint32 i = 0; i < meshGltf.normals.size(); i++) {
//            meshGltf.textureBitangent[i] = glm::cross(meshGltf.normals[i],
//                                                      glm::vec3(meshGltf.textureTangent[i].x,
//                                                                meshGltf.textureTangent[i].y,
//                                                                meshGltf.textureTangent[i].z))
//                                                                * meshGltf.textureTangent[i].w;
//        }
//    } else {
//        meshGltf.textureBitangent.resize(meshGltf.normals.size());
//        meshGltf.textureTangent.resize(meshGltf.normals.size());
//        for(Uint32 i = 0; i < meshGltf.normals.size(); i++) {
//            meshGltf.textureBitangent[i] = glm::vec3(0.05,0.06,0.05);
//            meshGltf.textureTangent[i] = glm::vec4(0.05,0.06,0.05, 1.0);
//        }
//    }

    // Vertex Tangent and Bi-tangent Calculation
    if(meshGltf.positions.size() == meshGltf.textureCoordinates.size()) {
        glm::vec3 vertex1;
        glm::vec3 vertex2;
        glm::vec3 vertex3;

        glm::vec2 uv1;
        glm::vec2 uv2;
        glm::vec2 uv3;

        glm::vec3 edge1;
        glm::vec3 edge2;

        GLfloat deltaU1;
        GLfloat deltaV1;
        GLfloat deltaU2;
        GLfloat deltaV2;

        GLfloat factor;
        glm::vec3 tangent, bitangent = glm::vec3(0.0,0.0,0.0);

        meshGltf.textureTangent.resize(meshGltf.positions.size());
        meshGltf.textureBitangent.resize(meshGltf.positions.size());

        for(Uint32 i = 0; i < meshGltf.indices.size(); i+=3) {
            Uint32 index1 = meshGltf.indices[i];
            Uint32 index2 = meshGltf.indices[i+1];
            Uint32 index3 = meshGltf.indices[i+2];

            vertex1 = meshGltf.positions[index1];
            vertex2 = meshGltf.positions[index2];
            vertex3 = meshGltf.positions[index3];

            uv1 = meshGltf.textureCoordinates[index1];
            uv2 = meshGltf.textureCoordinates[index2];
            uv3 = meshGltf.textureCoordinates[index3];

            edge1 = vertex2 - vertex1;
            edge2 = vertex3 - vertex1;

            deltaU1 = uv2.x - uv1.x;
            deltaV1 = uv2.y - uv1.y;
            deltaU2 = uv3.x - uv1.x;
            deltaV2 = uv3.y - uv1.y;

            factor = 1.0f / (deltaU1 * deltaV2 - deltaU2 * deltaV1);

            tangent.x = factor * (deltaV2 * edge1.x - deltaV1 * edge2.x);
            tangent.y = factor * (deltaV2 * edge1.y - deltaV1 * edge2.y);
            tangent.z = factor * (deltaV2 * edge1.z - deltaV1 * edge2.z);

            bitangent.x = factor * (-deltaU2 * edge1.x + deltaU1 * edge2.x);
            bitangent.y = factor * (-deltaU2 * edge1.y + deltaU1 * edge2.y);
            bitangent.z = factor * (-deltaU2 * edge1.z + deltaU1 * edge2.z);

            meshGltf.textureTangent[index1] = glm::normalize(glm::vec4(tangent, 1.0));
            meshGltf.textureTangent[index2] = glm::normalize(glm::vec4(tangent, 1.0));
            meshGltf.textureTangent[index3] = glm::normalize(glm::vec4(tangent, 1.0));

            meshGltf.textureBitangent[index1] = glm::normalize(glm::vec4(bitangent, 1.0));
            meshGltf.textureBitangent[index2] = glm::normalize(glm::vec4(bitangent, 1.0));
            meshGltf.textureBitangent[index3] = glm::normalize(glm::vec4(bitangent, 1.0));
        }
    }
    _fileGltf->meshes.push_back(meshGltf);
}

Material* createMaterial(MaterialGLTF materialGltf, FileGLTF *_fileGltf, ResourcesManager *resourcesManager) {
    auto* material = new Material(materialGltf.name.c_str(), nullptr);
    if(materialGltf.metallicRoughnessGltf.baseColorTexture != SDL_MAX_UINT8) {
        TextureGLTF textureGLTF = _fileGltf->textures[materialGltf.metallicRoughnessGltf.baseColorTexture];
        ImageGLTF imageGltf = _fileGltf->images[textureGLTF.source];
        auto* texture = new Texture();
        texture->name = imageGltf.name;
        texture->source = resourcesManager->pathToImagesResources + imageGltf.source;
        material->albedo = texture;
    }
    if(materialGltf.normalGltf.texture != SDL_MAX_UINT8) {
        TextureGLTF textureGLTF = _fileGltf->textures[materialGltf.normalGltf.texture];
        ImageGLTF imageGltf = _fileGltf->images[textureGLTF.source];
        auto* texture = new Texture();
        texture->name = imageGltf.name;
        texture->source = resourcesManager->pathToImagesResources + imageGltf.source;
        material->normal = texture;
    }
    if(materialGltf.heightGltf.texture != SDL_MAX_UINT8) {
        TextureGLTF textureGLTF = _fileGltf->textures[materialGltf.heightGltf.texture];
        ImageGLTF imageGltf = _fileGltf->images[textureGLTF.source];
        auto* texture = new Texture();
        texture->name = imageGltf.name;
        texture->source = resourcesManager->pathToImagesResources + imageGltf.source;
        material->height = texture;
    }
    return material;
}

Renderable* createModelFromNode(NodeGLTF *nodeGltf, MeshGLTF *meshGltf, FileGLTF *_fileGltf, ResourcesManager *resourcesManager) {
    auto* model = new Renderable();
    model->name = nodeGltf->name;
    model->position = nodeGltf->position;
    model->scale = nodeGltf->scale;
    model->eulerAngles = glm::eulerAngles(nodeGltf->rotation);
    model->rotation = nodeGltf->rotation;
    model->updateModelMatrix();
    model->vertices.insert(model->vertices.end(), meshGltf->positions.begin(), meshGltf->positions.end());
    model->index.insert(model->index.end(), meshGltf->indices.begin(), meshGltf->indices.end());
    model->normals.insert(model->normals.end(), meshGltf->normals.begin(), meshGltf->normals.end());
    model->tangent.insert(model->tangent.end(), meshGltf->textureTangent.begin(), meshGltf->textureTangent.end());
    model->bitangent.insert(model->bitangent.end(), meshGltf->textureBitangent.begin(), meshGltf->textureBitangent.end());
    model->texture.insert(model->texture.end(), meshGltf->textureCoordinates.begin(), meshGltf->textureCoordinates.end());
    model->weights.insert(model->weights.end(), meshGltf->weights.begin(), meshGltf->weights.end());
    if(meshGltf->material != SDL_MAX_UINT8) {
        model->material = createMaterial(_fileGltf->materials[meshGltf->material], _fileGltf, resourcesManager);
    }
    for(int i=0; i<meshGltf->joints.size();i+=4) {
        model->joints.push_back(glm::vec4(meshGltf->joints[i], meshGltf->joints[i+1], meshGltf->joints[i+2], meshGltf->joints[i+3]));
    }
    return model;
}

Skin* createSkinFromNode(SkinGLTF *skinGltf, std::vector<NodeGLTF>* nodes){
    auto *skin = new Skin();
    skin->name = skinGltf->name;
    int i = 0;
    for(auto& jointIndex : skinGltf->joints) {
        auto *joint = new Joint();
        joint->index = jointIndex;
        joint->name = (*nodes)[jointIndex].name;
        joint->rotation = (*nodes)[jointIndex].rotation;
        joint->eulerAngles = glm::eulerAngles(joint->rotation);
        joint->scale = (*nodes)[jointIndex].scale;
        joint->tall = (*nodes)[jointIndex].position;
        joint->jointToModelMatrix = skinGltf->inverseBindMatrices[i];
        for(auto& child : (*nodes)[jointIndex].children) {
            joint->children.push_back(child);
        }
        skin->joints.push_back(joint);
        i++;
    }
    for(auto& node : *nodes) {
        if(skin->name == node.name) {
            skin->position = node.position;
            skin->rotation = node.rotation;
            skin->origin = skin->position * glm::toMat4(skin->rotation);
            skin->worldToSkinMatrix = skin->worldToSkinMatrix * glm::toMat4(skin->rotation);
            skin->worldToSkinMatrix[3].x = skin->position.x;
            skin->worldToSkinMatrix[3].y = skin->position.y;
            skin->worldToSkinMatrix[3].z = skin->position.z;
        }
    }
    return skin;
}

void createSkinHierarchy(Skin *skin) {
    for(auto& joint : skin->joints) {
        for(auto& child : joint->children) {
            for(auto& jointChild : skin->joints) {
                if(jointChild->index == child) {
                    jointChild->parent = joint;
                    joint->childrenObjects.push_back(jointChild);
                    break;
                }
            }
        }
    }
    for(auto& joint : skin->joints) {
        if(joint->parent == nullptr) {
            joint->modelToJointMatrix = joint->modelToJointMatrix * skin->worldToSkinMatrix;
        }
        glm::vec4 rotatedTall = joint->modelToJointMatrix * joint->tall;
        joint->modelToJointMatrix = joint->modelToJointMatrix * glm::toMat4(joint->rotation);
        joint->modelToJointMatrix[3].x += rotatedTall.x;
        joint->modelToJointMatrix[3].y += rotatedTall.y;
        joint->modelToJointMatrix[3].z += rotatedTall.z;
        for(auto& child : joint->childrenObjects) {
            child->modelToJointMatrix = child->modelToJointMatrix * joint->modelToJointMatrix;
        }
        joint->size.resize(2);
        joint->size[0] = joint->modelToJointMatrix * glm::vec4(0.0,0.0,0.0,1.0);
        joint->size[1] = joint->modelToJointMatrix * glm::vec4(0.0,1.0,0.0,1.0);
    }

    skin->currentAnimationMatrices.resize(skin->joints.size());
    skin->modelToJointMatrices.resize(skin->joints.size());
//    skin->setCurrentAnimationMatricesIdentity();
}

void loadGLTFSampler(Animation* _animation, std::vector<ChannelGLTF>* channels, float *animationStartTime, float *animationEndTime, Skin* _skin) {
    int index = 0;
    for(auto& joint : _skin->joints) {
        std::vector<glm::vec4>* rotation = nullptr;
        std::vector<glm::vec3>* translation = nullptr;
        std::vector<float>* keyFrames = nullptr;

        for(auto& channel : *channels) {
            if(channel.node == joint->index && channel.targetName == "translation") {
                translation = &(channel.translation);
            }
            if(channel.node == joint->index && channel.targetName == "rotation") {
                rotation = &(channel.rotation);
                keyFrames = &(channel.keyframes);
            }
        }

        if(keyFrames != nullptr) {
            for(int i = 0; i < keyFrames->size() - 1; i++) {
                auto *sampler = new Sampler();
                sampler->start = (*keyFrames)[i];
                if (sampler->start < *animationStartTime) {
                    *animationStartTime = sampler->start;
                }
                sampler->end = (*keyFrames)[i + 1];
                if (sampler->end > *animationEndTime) {
                    *animationEndTime = sampler->end;
                }
                sampler->timeDifference = sampler->end - sampler->start;

                if(translation != nullptr) {
                    sampler->startRotation = glm::quat((*rotation)[i].w, (*rotation)[i].x, (*rotation)[i].y, (*rotation)[i].z);
                    sampler->endRotation = glm::quat((*rotation)[i + 1].w, (*rotation)[i + 1].x, (*rotation)[i + 1].y, (*rotation)[i + 1].z);
                }

                if(translation != nullptr) {
                    sampler->startPosition = (*translation)[i];
                    sampler->endPosition = (*translation)[i + 1];
                }
                sampler->startEuler = glm::eulerAngles(sampler->startRotation);
                sampler->endEuler = glm::eulerAngles(sampler->endRotation);

                sampler->interpolationVector = sampler->endRotation - sampler->startRotation;
                _animation->animatedBones[index]->samplers.push_back(sampler);
            }
            if(!_animation->animatedBones.empty() && _animation->animatedBones[index] != nullptr && !_animation->animatedBones[index]->samplers.empty()) {
                _animation->animatedBones[index]->currentSampler = _animation->animatedBones[index]->samplers[0];
            }
        }
        index++;
    }
}

void createAnimationFromNode(ResourcesManager *_resourceManager, const std::string& skinName, AnimationGLTF *_animationGltf) {
    auto *animation = new Animation();
    animation->name = _animationGltf->name;

    auto *skin = _resourceManager->getSkin(skinName.c_str());

    for(int i = 0; i < skin->joints.size(); i ++) {
        animation->animatedBones.push_back(new AnimatedBone());
    }
//    loadGLTFSampler(animation, &(_animationGltf->channels), &(animation->startTime), &(animation->endTime), skin);
    skin->animations.insert(std::pair<std::string, Animation*>(animation->name, animation));
//    skin->currentAnimation = animation;
}

void ResourcesManager::createEngineElements(FileGLTF *_fileGltf) {
    for(auto& node : _fileGltf->nodes) {
        if(node.mesh != SDL_MAX_UINT8) {
            this->models.insert(std::pair<std::string, Renderable*>(node.name, createModelFromNode(&node, &(_fileGltf->meshes[node.mesh]), _fileGltf, this)));
        }
    }
    for(auto& skinGltf : _fileGltf->skins) {
        auto *skin = createSkinFromNode(&skinGltf, &(_fileGltf->nodes));
        createSkinHierarchy(skin);
        this->skins.insert(std::pair<std::string,Skin*>(skinGltf.name, skin));
    }
    for(auto& animationGltf : _fileGltf->animations) {
        createAnimationFromNode(this, _fileGltf->skins[0].name, &animationGltf);
    }
}

void loadGLTFSkinFromFile(FileGLTF *_fileGltf, Json::Value _skin, const Json::Value& _accessors, const Json::Value& _buffersViews, std::ifstream *_jsonFile) {
    SkinGLTF skinGltf;
    skinGltf.name = _skin["name"].asString();

    Uint32 inversedMatrixAccessor = _skin["inverseBindMatrices"].as<Uint32>();
    Uint32 inversedMatrixBufferView = _accessors[inversedMatrixAccessor]["bufferView"].as<Uint32>();
    std::string inversedMatrixBufferViewType = _accessors[inversedMatrixAccessor]["type"].asString();
    Uint32 count = _accessors[inversedMatrixAccessor]["count"].as<Uint32>();
    std::streamoff byteOffset = _buffersViews[inversedMatrixBufferView]["byteOffset"].as<std::streamoff>();
    std::streamoff arrayByteLenght = _buffersViews[inversedMatrixBufferView]["byteLength"].as<std::streamoff>();

    if(_jsonFile->is_open() && inversedMatrixBufferViewType == "MAT4") {
        skinGltf.inverseBindMatrices.resize(count);
        _jsonFile->seekg(byteOffset);
        _jsonFile->read((char*)skinGltf.inverseBindMatrices.data(), arrayByteLenght);
    }

    for(const Json::Value& joint : _skin["joints"]) {
        skinGltf.joints.push_back(joint.as<Uint32>());
    }
    _fileGltf->skins.push_back(skinGltf);
}

void loadGLTFAnimationFromFile(FileGLTF *_fileGltf, Json::Value _animation, const Json::Value& _accessors, const Json::Value& _buffersViews, std::ifstream *_jsonFile) {
    AnimationGLTF animationGltf;
    animationGltf.name = _animation["name"].asString();
    for(Json::Value channel : _animation["channels"]) {
        ChannelGLTF channelGltf;
        Uint32 sampler = channel["sampler"].as<Uint32>();
        channelGltf.node = channel["target"]["node"].as<Uint32>();
        channelGltf.targetName = channel["target"]["path"].asString();

        if(channelGltf.targetName == "rotation") {
            Uint32 input = _animation["samplers"][sampler]["input"].as<Uint32>();
            Uint32 output = _animation["samplers"][sampler]["output"].as<Uint32>();

            Uint32 bufferView = _accessors[input]["bufferView"].as<Uint32>();
            Uint32 count = _accessors[input]["count"].as<Uint32>();
            std::string type = _accessors[input]["type"].asString();

            Uint32 byteOffsetChannel = _buffersViews[bufferView]["byteOffset"].as<Uint32>();
            Uint32 byteLength = _buffersViews[bufferView]["byteLength"].as<Uint32>();

            Uint32 outputBufferView = _accessors[output]["bufferView"].as<Uint32>();
            Uint32 outputCount = _accessors[output]["count"].as<Uint32>();
            std::string outputType = _accessors[output]["type"].asString();

            Uint32 outputByteOffset = _buffersViews[outputBufferView]["byteOffset"].as<Uint32>();
            Uint32 outputByteLength = _buffersViews[outputBufferView]["byteLength"].as<Uint32>();

            channelGltf.keyframes.resize(count);
            _jsonFile->seekg(byteOffsetChannel);
            _jsonFile->read((char *) channelGltf.keyframes.data(), byteLength);

            channelGltf.rotation.resize(count);
            _jsonFile->seekg(outputByteOffset);
            _jsonFile->read((char *) channelGltf.rotation.data(), outputByteLength);
        }

        if(channelGltf.targetName == "translation") {
            Uint32 input = _animation["samplers"][sampler]["input"].as<Uint32>();
            Uint32 output = _animation["samplers"][sampler]["output"].as<Uint32>();

            Uint32 bufferView = _accessors[input]["bufferView"].as<Uint32>();
            Uint32 count = _accessors[input]["count"].as<Uint32>();
            std::string type = _accessors[input]["type"].asString();

            Uint32 byteOffsetChannel = _buffersViews[bufferView]["byteOffset"].as<Uint32>();
            Uint32 byteLength = _buffersViews[bufferView]["byteLength"].as<Uint32>();

            Uint32 outputBufferView = _accessors[output]["bufferView"].as<Uint32>();
            Uint32 outputCount = _accessors[output]["count"].as<Uint32>();
            std::string outputType = _accessors[output]["type"].asString();

            Uint32 outputByteOffset = _buffersViews[outputBufferView]["byteOffset"].as<Uint32>();
            Uint32 outputByteLength = _buffersViews[outputBufferView]["byteLength"].as<Uint32>();

            channelGltf.keyframes.resize(count);
            _jsonFile->seekg(byteOffsetChannel);
            _jsonFile->read((char *) channelGltf.keyframes.data(), byteLength);

            channelGltf.translation.resize(count);
            _jsonFile->seekg(outputByteOffset);
            _jsonFile->read((char *) channelGltf.translation.data(), outputByteLength);
        }
        animationGltf.channels.push_back(channelGltf);
    }
    _fileGltf->animations.push_back(animationGltf);
}

void loadGLTFNodeFromFile(FileGLTF *_fileGltf, Json::Value _node, const Json::Value& _accessors, const Json::Value& _buffersViews, std::ifstream *_jsonFile) {
    NodeGLTF nodeGltf;
    nodeGltf.name = _node["name"].asString();

    if(!_node["translation"].isNull()) {
        nodeGltf.position = glm::vec4(_node["translation"][0].asFloat(), _node["translation"][1].asFloat(), _node["translation"][2].asFloat(), 0.0f);
    }
    if(!_node["mesh"].isNull()) {
        nodeGltf.mesh =_node["mesh"].as<Uint32>();
    }
    if(!_node["scale"].isNull()) {
        nodeGltf.scale = glm::vec3(_node["scale"][0].asFloat(), _node["scale"][1].asFloat(), _node["scale"][2].asFloat());
    }
    if(!_node["rotation"].isNull()) {
        nodeGltf.rotation = glm::quat(_node["rotation"][3].asFloat(), _node["rotation"][0].asFloat(), _node["rotation"][1].asFloat(), _node["rotation"][2].asFloat());
    }
    if(!_node["children"].isNull()) {
        for(const Json::Value& child : _node["children"]) {
            nodeGltf.children.push_back(child.as<Uint32>());
        }
    }
    _fileGltf->nodes.push_back(nodeGltf);
}

void loadGLTFImagesFromFile(FileGLTF *_fileGltf, Json::Value _image) {
    ImageGLTF image;
    image.name = _image["name"].asString();
    image.source = _image["uri"].asString();
    _fileGltf->images.push_back(image);
}

void loadGLTFTexturesFromFile(FileGLTF *_fileGltf, Json::Value _texture) {
    TextureGLTF texture;
    texture.source = _texture["source"].as<Uint32>();
    texture.sampler = _texture["sampler"].as<Uint32>();
    _fileGltf->textures.push_back(texture);
}

void loadGLTFMaterialsFromFile(FileGLTF *_fileGltf, Json::Value _material) {
    MaterialGLTF material;
    material.name = _material["name"].asString();
    if(!_material["pbrMetallicRoughness"]["baseColorTexture"]["index"].isNull()) {
        material.metallicRoughnessGltf.baseColorTexture = _material["pbrMetallicRoughness"]["baseColorTexture"]["index"].as<Uint32>();
    }
    if(!_material["pbrMetallicRoughness"]["roughnessFactor"].isNull()) {
        material.metallicRoughnessGltf.roughnessFactor = _material["pbrMetallicRoughness"]["roughnessFactor"].as<GLfloat>();
    }
    if(!_material["pbrMetallicRoughness"]["metallicFactor"].isNull()) {
        material.metallicRoughnessGltf.metallicFactor = _material["pbrMetallicRoughness"]["metallicFactor"].as<GLfloat>();
    }
    if(!_material["normalTexture"]["index"].isNull()) {
        material.normalGltf.texture = _material["normalTexture"]["index"].as<Uint32>();
    }
    if(!_material["heightTexture"]["index"].isNull()) {
        material.heightGltf.texture = _material["heightTexture"]["index"].as<Uint32>();
    }
    _fileGltf->materials.push_back(material);
}

void ResourcesManager::loadGLTFModel(const char* pathToModel) {
    std::ifstream jsonFile;
    JSONCPP_STRING err;
    Json::Value root;
    Json::CharReaderBuilder builder;
    jsonFile.open(pathToModel);

    if (!parseFromStream(builder, jsonFile, &root, &err)) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, std::string("Error reading:").append(pathToModel).c_str());
    }

    std::string pathToBinaryFile(this->pathToModelResources);
    pathToBinaryFile.append(root["buffers"][0]["uri"].asString());
    std::ifstream dataBufferFile;
    dataBufferFile.open(pathToBinaryFile, std::ios::binary);
    FileGLTF fileGltf;
    if(!root["nodes"].isNull()) {
        for(const Json::Value& node : root["nodes"]) {
            loadGLTFNodeFromFile(&fileGltf, node, root["accessors"], root["bufferViews"], &dataBufferFile);
        }
    }
    if(!root["meshes"].isNull()) {
        for(const Json::Value& mesh : root["meshes"]) {
            loadGLTFMeshFromFile(&fileGltf, mesh, root["accessors"], root["bufferViews"], &dataBufferFile);
        }
    }
    if(!root["skins"].isNull()) {
        for(const Json::Value& skin : root["skins"]) {
            loadGLTFSkinFromFile(&fileGltf, skin, root["accessors"], root["bufferViews"], &dataBufferFile);
        }
    }
    if(!root["animations"].isNull()) {
        for(const Json::Value& animation : root["animations"]) {
            loadGLTFAnimationFromFile(&fileGltf, animation, root["accessors"], root["bufferViews"], &dataBufferFile);
        }
    }
    if(!root["materials"].isNull()) {
        for(const Json::Value& material : root["materials"]) {
            loadGLTFMaterialsFromFile(&fileGltf, material);
        }
    }
    if(!root["textures"].isNull()) {
        for(const Json::Value& texture : root["textures"]) {
            loadGLTFTexturesFromFile(&fileGltf, texture);
        }
    }
    if(!root["images"].isNull()) {
        for(const Json::Value& image : root["images"]) {
            loadGLTFImagesFromFile(&fileGltf, image);
        }
    }
    dataBufferFile.close();
    jsonFile.close();
    createEngineElements(&fileGltf);
}

void ResourcesManager::printModelInformation(Renderable* _model) {
//    if(this->logManager != nullptr) {
//        this->logManager->info(std::string("|        Model: ").append(_model->name));
//        this->logManager->info(std::string("|            Vertex: ").append(std::to_string(_model->vertices.size())));
//        this->logManager->info(std::string("|            Normal: ").append(std::to_string(_model->normals.size())));
//        this->logManager->info(std::string("|            Texture: ").append(std::to_string(_model->texture.size())));
//        this->logManager->info(std::string("|            Indices: ").append(std::to_string(_model->index.size())));
//    }
}

Renderable* ResourcesManager::getRenderable(const char * _modelName) {
    auto result = this->models.find(_modelName);
    if(result != this->models.end()){
        return result->second;
    }
    return nullptr;
}

Skin* ResourcesManager::getSkin(const char * _skinName) {
    auto result = this->skins.find(_skinName);
    if(result != this->skins.end()){
        return result->second;
    }
    return nullptr;
}

