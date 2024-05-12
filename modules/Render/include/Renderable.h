#ifndef ENGINETEST_RENDERABLE_OPENGL_H
#define ENGINETEST_RENDERABLE_OPENGL_H

#include <glm/detail/type_quat.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <vector>
#include <string>
#include <SDLAPI.h>
#include <OpenGLAPI.h>

class Material;
class ShaderManager;
class Renderable {
public:
    std::string name;
    Material *material = nullptr;
    glm::mat4x4 modelMatrix = glm::mat4x4(1.0f,0.0f,0.0f,0.0f,
                                          0.0f,1.0f,0.0f,0.0f,
                                          0.0f,0.0f,1.0f,0.0f,
                                          0.0f,0.0f,0.0f,1.0f);
    glm::vec3 position = glm::vec3(0.0,0.0,0.0);
    glm::quat rotation = glm::quat (0.0,0.0,0.0,1.0);
    glm::vec3 eulerAngles = glm::vec3(0.0,0.0,0.0);
    glm::vec3 scale = glm::vec3(0.0,0.0,0.0);
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> texture;
    std::vector<glm::vec3> tangent;
    std::vector<glm::vec3> bitangent;
    std::vector<glm::vec4> joints;
    std::vector<glm::vec4> weights;
    std::vector<UnsignedInteger32> index;

    UnsignedInteger32 vao = UNSIGNED_INTEGER_MAX_32;
    UnsignedInteger32 vertexVBO = UNSIGNED_INTEGER_MAX_32;
    UnsignedInteger32 normalVBO = UNSIGNED_INTEGER_MAX_32;
    UnsignedInteger32 tangentVBO = UNSIGNED_INTEGER_MAX_32;
    UnsignedInteger32 bitangentVBO = UNSIGNED_INTEGER_MAX_32;
    UnsignedInteger32 textureVBO = UNSIGNED_INTEGER_MAX_32;
    UnsignedInteger32 indexVBO = UNSIGNED_INTEGER_MAX_32;

    Renderable() = default;
    ~Renderable() = default;

    void prepareMaterial(ShaderManager*);
    void setPosition(Float x, Float y, Float z);
    void setRotation(Float roll, Float pitch, Float yaw);
    void updateModelMatrix();

};

#endif //ENGINETEST_RENDERABLE_OPENGL_H
