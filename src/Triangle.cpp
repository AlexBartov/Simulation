#include "Triangle.h"

Triangle::Triangle()
{
}

Triangle::Triangle(const glm::vec3 &A, const glm::vec3 &B, const glm::vec3 &C)
{
    this->A = A;
    this->B = B;
    this->C = C;
}

glm::vec3 Triangle_::mid(const glm::vec3 &A, const glm::vec3 B)
{
    return glm::vec3((A.x+B.x)/2.0f, (A.y+B.y)/2.0f, (A.z+B.z)/2.0f);
}
