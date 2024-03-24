#ifndef ENGINETEST_RENDERABLE_H
#define ENGINETEST_RENDERABLE_H

#include <glm/detail/type_quat.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include <GL/glew.h>

class Material;
class Renderable {
public:
    glm::vec3 position;
    glm::quat rotation;
    glm::vec3 eulerAngles;
    glm::vec3 scale;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> texture;
    std::vector<glm::vec4> joints;
    std::vector<glm::vec4> weights;
    std::vector<GLuint> index;
    Material *material;
    glm::mat4x4 modelMatrix = glm::mat4x4(1.0f,0.0f,0.0f,0.0f,
                                          0.0f,1.0f,0.0f,0.0f,
                                          0.0f,0.0f,1.0f,0.0f,
                                          0.0f,0.0f,0.0f,1.0f);
    std::string name;

    Renderable() = default;
    ~Renderable() = default;

    void setPosition(GLfloat x, GLfloat y, GLfloat z);
    void setRotation(GLfloat roll, GLfloat pitch, GLfloat yaw);
    void updateModelMatrix();
};

#endif //ENGINETEST_RENDERABLE_H
