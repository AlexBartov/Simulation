#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>


class Triangle
{
public:
    Triangle();
    Triangle(const glm::vec3 &A, const glm::vec3 &B, const glm::vec3 &C);
    glm::vec3 A;
    glm::vec3 B;
    glm::vec3 C;
};

namespace Triangle_
{
    glm::vec3 mid(const glm::vec3 &A, const glm::vec3 B);
}

#endif // TRIANGLE_H
