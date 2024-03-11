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
    glm::vec4 position;
    glm::quat rotation;
    glm::vec3 scale;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> texture;
    std::vector<glm::vec4> joints;
    std::vector<glm::vec4> weights;
    std::vector<GLuint> index;
    Material *material;
    std::string name;

    Renderable() = default;
    ~Renderable() = default;
};

#endif //ENGINETEST_RENDERABLE_H
