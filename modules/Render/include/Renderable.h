#ifndef ENGINETEST_RENDERABLE_OPENGL_H
#define ENGINETEST_RENDERABLE_OPENGL_H

#include <glm/detail/type_quat.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include <GL/glew.h>

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
    std::vector<GLuint> index;

    Uint16 vao = SDL_MAX_UINT16;
    Uint16 vertexVBO = SDL_MAX_UINT16;
    Uint16 normalVBO = SDL_MAX_UINT16;
    Uint16 tangentVBO = SDL_MAX_UINT16;
    Uint16 bitangentVBO = SDL_MAX_UINT16;
    Uint16 textureVBO = SDL_MAX_UINT16;
    Uint16 indexVBO = SDL_MAX_UINT16;

    Renderable() = default;
    ~Renderable() = default;

    void prepareMaterial(ShaderManager*);
    void setPosition(GLfloat x, GLfloat y, GLfloat z);
    void setRotation(GLfloat roll, GLfloat pitch, GLfloat yaw);
    void updateModelMatrix();

};

#endif //ENGINETEST_RENDERABLE_OPENGL_H
